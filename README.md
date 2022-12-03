### Introduction

This my old projects about audio editing. They were created as course and diploma projects at college.
I look at code and it is awful. However they bring up a lot of good memories of those times. So I decided don't touch them.
If you wanna fix them: great!

***Attention!*** A lot of comments and strings in russian. If you need translation then write to me and I will help you.

### Description


Due to WinApi and MFC don't work with .mp3 properly I used **bass.dll**. 
I want to thank these great people for their work. 
Please read more about bass.dll and its add-ons on their [site](https://www.un4seen.com).

***About issue in WinApi/MFC:*** WinApi functions incorrectly determine the duration of .mp3 files with variable bit rate.
However Windows Media Player hasn't that issue, that's because it uses DirectX Sound, but WinApi/MFC doesn't use DirectX.
***Interesting note:*** as I know QT have the same issue on Windows, because it uses native functions which are WinApi.
I don't know if this issue still exists, but something tells me that it hasn't been solved yet.

### How to build

Projects were created in Visual Studio 2013 using MFC and C++98 or C++11. Tested only on 32-bit platform.

You need to:
1. Install Visual Studio 2013 or higher (I tested in Visual Studio 2019 and it still works)
2. Install MFC component.
3. Retarget solution
4. ???
5. Build
6. Profit! It works.

### Files that need to start a program

**SoundEditor**
- `Course.exe` <= you generate it
- `bass.dll` & `bassenc.dll` - bass.dll and its add-on
- `lame.exe` & `lame_enc.dll` - used for saving .mp3 files. More [here](https://lame.sourceforge.io).
- (EqualUser.txt) - user settings for equlizer. I can't remember is it necessary or not.
I think no, because program generates it, if doesn't exists. However there can be a bug.

**AudioCreator**
- `AudioCreator.exe` <= you generate it
- `bass.dll`, `bassflac.dll`, `bassenc.dll`, `basswma.dll`, `basswv.dll`, `bass_mpc.dll`, 
`bass_ape.dll`, `bass_tta.dll`, `bass_fx.dll` - bass.dll and its add-ons
- `lame.exe` & `lame_enc.dll` - look above
- `wavpack.exe` - used for saving .wav files. [Here](https://www.wavpack.com) for more information.
- `oggenc2.exe` - used for saving .ogg files. [Here](https://www.rarewares.org/ogg-oggenc.php) for more information.
As [here](https://wiki.hydrogenaud.io/index.php?title=Oggenc) said: oggenc2 is an enhanced version of oggenc developed by John33. 
Features compression from lossless files (Monkey's Audio, LPAC, FLAC, OptimFROG, WavPack and Shorten - requires presence of decoders), 
and the ability to specify "padding" in the headers for subsequent insertion of tags. So I think I used it not only for .ogg files, but who knows...

### Need help?

Write to me and I will try to help you.

### Donations

If you want to donate someone or contribute somewhere, please, do it to projects I used, 
because they are awesome and their authors need your support.

- Bass.dll - *[link](https://www.un4seen.com)*
- LAME MP3 Encoder - *[link](https://lame.sourceforge.io)*
- WavPack Audio Compression - *[link](https://www.wavpack.com)*
- oggenc2 - *[link](https://rarewares.org/)*
- oggenc - *[link](https://www.xiph.org)*