#include "MarmaladeEffectsLibrary.h"

#include <TLFXEffectsLibrary.h>
#include <TLFXParticleManager.h>
#include <TLFXEffect.h>

#include <IwGx.h>
#include <s3eKeyboard.h>
#include <s3ePointer.h>

// Attempt to lock to 25 frames per second
#define MS_PER_FRAME (1000 / 25)

TLFX::EffectsLibrary *gEffects = NULL;
MarmaladeParticleManager *gPM = NULL;

void Init()
{
	IwGxInit();
    IwGxLightingOff();

    gEffects = new MarmaladeEffectsLibrary();
    gEffects->Load("particles/data.xml");

    gPM = new MarmaladeParticleManager();
    gPM->SetScreenSize(IwGxGetScreenWidth(), IwGxGetScreenHeight());
    gPM->SetOrigin(0, 0);

    TLFX::Effect *eff = gEffects->GetEffect("Area Effects/Swirly Balls");
    TLFX::Effect *copy = new TLFX::Effect(*eff, gPM);

    copy->SetPosition(0.0f, 0.0f);
    gPM->AddEffect(copy);
}

void ShutDown()
{
    delete gEffects;
    delete gPM;

    IwGxTerminate();
}

bool Update()
{
    gPM->Update();
	return true;
}

void Render()
{
    // Clear the screen
    IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);

    gPM->DrawParticles();
    gPM->Flush();

    IwGxFlush();
    IwGxSwapBuffers();
}

S3E_MAIN_DECL void IwMain()
{
    Init();

    // Set screen clear colour
    IwGxSetColClear(0, 0, 0, 0xff);
    IwGxPrintSetColour(128, 128, 128);

    while (1)
    {
        s3eDeviceYield(0);
        s3eKeyboardUpdate();
        s3ePointerUpdate();

        int64 start = s3eTimerGetMs();

        bool result = Update();
        if  (
            ((result == false) ||
            (s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN) ||
            (s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN) ||
            (s3eDeviceCheckQuitRequest()))
            )
            break;

        Render();

        // Attempt frame rate
        while ((s3eTimerGetMs() - start) < MS_PER_FRAME)
        {
            int32 yield = (int32) (MS_PER_FRAME - (s3eTimerGetMs() - start));
            if (yield<0)
                break;
            s3eDeviceYield(yield);
        }
    }

    ShutDown();
}
