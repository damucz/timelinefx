#include "MarmaladeEffectsLibrary.h"
#include "TLFXPugiXMLLoader.h"

#include <IwGx.h>

#include <cmath>

TLFX::XMLLoader* MarmaladeEffectsLibrary::CreateLoader() const
{
    return new TLFX::PugiXMLLoader(0);
}

TLFX::AnimImage* MarmaladeEffectsLibrary::CreateImage() const
{
    return new MarmaladeImage();
}



bool MarmaladeImage::Load( const char *filename )
{
    _texture = new CIwTexture();
    _texture->LoadFromFile(filename);
    _texture->Upload();           //upload on load?
    // how to detect failure?
    return true;
}

MarmaladeImage::MarmaladeImage()
    : _texture(NULL)
{

}

MarmaladeImage::~MarmaladeImage()
{
    if (_texture)
        delete _texture;
}

CIwTexture* MarmaladeImage::GetTexture() const
{
    return _texture;
}

MarmaladeParticleManager::MarmaladeParticleManager( int particles /*= particleLimit*/, int layers /*= 1*/ )
    : TLFX::ParticleManager(particles, layers)
    , _lastSprite(NULL)
    , _lastAdditive(true)
{

}

void MarmaladeParticleManager::DrawSprite( TLFX::AnimImage* sprite, float px, float py, float frame, float x, float y, float rotation, float scaleX, float scaleY, unsigned char r, unsigned char g, unsigned char b, float a , bool additive )
{
    IwAssert(MARM, frame == 0);

    unsigned char alpha = (unsigned char)(a * 255);
    if (alpha == 0 || scaleX == 0 || scaleY == 0) return;

    if (sprite != _lastSprite || additive != _lastAdditive)
        Flush();

    Batch batch;
    batch.px = px;
    batch.py = py;
    batch.frame = frame;
    batch.x = x;
    batch.y = y;
    batch.rotation = rotation;
    batch.scaleX = scaleX;
    batch.scaleY = scaleY;
    batch.color.Set(r, g, b, alpha);
    _batch.push_back(batch);

    _lastSprite = sprite;
    _lastAdditive = additive;
}

void MarmaladeParticleManager::Flush()
{
    if (!_batch.empty() && _lastSprite)
    {
        int count = _batch.size();
        int count4 = count * 4;

        CIwColour *colors = IW_GX_ALLOC(CIwColour, count4);
        CIwFVec2 *uvs = IW_GX_ALLOC(CIwFVec2, count4);
        CIwFVec2 *verts = IW_GX_ALLOC(CIwFVec2, count4);
        uint16 *indices = IW_GX_ALLOC(uint16, count4);

        int index = 0;
        for (auto it = _batch.begin(); it != _batch.end(); ++it, index += 4)
        {
            for (int i = 0; i < 4; ++i)
            {
                colors[index + i].Set(it->color.r, it->color.g, it->color.b, it->color.a);
                indices[index + i] = index + i;
            }

            uvs[index + 0].x = 0;
            uvs[index + 0].y = 0;
            uvs[index + 1].x = 1.0f;
            uvs[index + 1].y = 0;
            uvs[index + 2].x = 1.0f;
            uvs[index + 2].y = 1.0f;
            uvs[index + 3].x = 0;
            uvs[index + 3].y = 1.0f;


            /*
            verts[index + 0].x = it->px - it->x * it->scaleX;
            verts[index + 0].y = it->py - it->y * it->scaleY;
            //verts[index + 0].z = 1.0f;
            verts[index + 1].x = verts[index + 0].x + _lastSprite->GetWidth() * it->scaleX;
            verts[index + 1].y = verts[index + 0].y;
            //verts[index + 1].z = 1.0f;
            verts[index + 2].x = verts[index + 1].x;
            verts[index + 2].y = verts[index + 1].y + _lastSprite->GetHeight() * it->scaleY;
            //verts[index + 2].z = 1.0f;
            verts[index + 3].x = verts[index + 0].x;
            verts[index + 3].y = verts[index + 2].y;
            //verts[index + 3].z = 1.0f;
            */

            float x0 = -it->x * it->scaleX;
            float y0 = -it->y * it->scaleY;
            float x1 = x0;
            float y1 = (-it->y + _lastSprite->GetHeight()) * it->scaleY;
            float x2 = (-it->x + _lastSprite->GetWidth()) * it->scaleX;
            float y2 = y1;
            float x3 = x2;
            float y3 = y0;

            float cos = cosf(it->rotation / 180.f * (float)M_PI);
            float sin = sinf(it->rotation / 180.f * (float)M_PI);

            verts[index + 0].x = it->px + x0 * cos - y0 * sin;
            verts[index + 0].y = it->py + x0 * sin + y0 * cos;
            //verts[index + 0].z = 1.0f;
            verts[index + 1].x = it->px + x1 * cos - y1 * sin;
            verts[index + 1].y = it->py + x1 * sin + y1 * cos;
            //verts[index + 1].z = 1.0f;
            verts[index + 2].x = it->px + x2 * cos - y2 * sin;
            verts[index + 2].y = it->py + x2 * sin + y2 * cos;
            //verts[index + 2].z = 1.0f;
            verts[index + 3].x = it->px + x3 * cos - y3 * sin;
            verts[index + 3].y = it->py + x3 * sin + y3 * cos;
            //verts[index + 3].z = 1.0f;
        }

        //IwGxSetModelMatrix(&modelTransform);
        IwGxSetUVStream(uvs);
        IwGxSetVertStreamScreenSpace(verts, count4);
        IwGxSetColStream(colors, count4);
        IwGxSetNormStream(NULL);

        CIwMaterial* mat = IW_GX_ALLOC_MATERIAL();
        mat->SetTexture(static_cast<MarmaladeImage*>(_lastSprite)->GetTexture());
        mat->SetDepthWriteMode(CIwMaterial::DEPTH_WRITE_DISABLED);
        mat->SetAlphaMode(_lastAdditive ? CIwMaterial::ALPHA_ADD : CIwMaterial::ALPHA_BLEND);
        IwGxSetMaterial(mat);

        IwGxDrawPrims(IW_GX_QUAD_LIST, indices, count4);

        _batch.clear();
    }
}
