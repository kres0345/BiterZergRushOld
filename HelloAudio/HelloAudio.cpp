// HelloAudio.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <AL/al.h>
#include <AL/alc.h>
#include <AudioFile/AudioFile.h>

#define OpenAL_ErrorCheck(message)\
{\
    ALenum error = alGetError();\
    if (error != AL_NO_ERROR)\
    {\
        std::cerr << "OpenAL Error: " << error << " with call for " << #message << std::endl;\
    }\
}

#define alec(FUNCTION_CALL)\
FUNCTION_CALL;\
OpenAL_ErrorCheck(FUNCTION_CALL)

int main()
{
    const ALCchar* defaultDeviceString = alcGetString(nullptr, ALC_DEFAULT_DEVICE_SPECIFIER);
    ALCdevice* device = alcOpenDevice(defaultDeviceString);

    if (!device)
    {
        std::cerr << "failed default device!" << std::endl;
        return -1;
    }

    std::cout << "OpenAL Device: " << alcGetString(device, ALC_DEVICE_SPECIFIER) << std::endl;
    OpenAL_ErrorCheck(device);

    ALCcontext* context = alcCreateContext(device, nullptr);
    OpenAL_ErrorCheck(context);

    if (!alcMakeContextCurrent(context))
    {
        std::cerr << "failed to open context" << std::endl;
        return -1;
    }
    OpenAL_ErrorCheck("Make context current");

    alec(alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f));
    alec(alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f));

    AudioFile<float> monoSoundFile;
    if (!monoSoundFile.load("sounds/biter-death-1.wav"))
    {
        std::cerr << "no load file" << std::endl;
        return -1;
    }

    std::vector<uint8_t> monoPCMDataBytes;
    

    std::cout << "Hello World!\n";


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
