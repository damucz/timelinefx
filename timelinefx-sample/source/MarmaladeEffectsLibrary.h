#ifdef _MSC_VER
#pragma once
#endif

/*
 * Marmalade IwGx for rendering
 * PugiXML for parsing data
 */

#ifndef _MARMALADEEFFECTSLIBRARY_H
#define _MARMALADEEFFECTSLIBRARY_H

#include "TLFXEffectsLibrary.h"
#include "TLFXParticleManager.h"
#include "TLFXAnimImage.h"

#include <IwTexture.h>

class XMLLoader;

class MarmaladeEffectsLibrary : public TLFX::EffectsLibrary
{
public:
    virtual TLFX::XMLLoader* CreateLoader() const;
    virtual TLFX::AnimImage* CreateImage() const;
};

class MarmaladeParticleManager : public TLFX::ParticleManager
{
public:
    MarmaladeParticleManager(int particles = TLFX::ParticleManager::particleLimit, int layers = 1);
    void Flush();
protected:
    virtual void DrawSprite(TLFX::AnimImage* sprite, float px, float py, float frame, float x, float y, float rotation,
                            float scaleX, float scaleY, unsigned char r, unsigned char g, unsigned char b, float a, bool additive);

    // batching
    struct Batch
    {
        float px, py;
        float frame;
        float x, y;
        float rotation;
        float scaleX, scaleY;
        CIwColour color;
    };
    std::list<Batch> _batch;
    TLFX::AnimImage *_lastSprite;
    bool             _lastAdditive;
};

class MarmaladeImage : public TLFX::AnimImage
{
public:
    MarmaladeImage();
    ~MarmaladeImage();

    bool Load(const char *filename);
    CIwTexture* GetTexture() const;

protected:
    CIwTexture *_texture;
};

#endif // _MARMALADEEFFECTSLIBRARY_H
