//Copyright 2021 zbt
//license: MIT
//Author zbt
//This is a plane war key class: Music_Player, play the game music;
#pragma once
#include<windows.h>

#include<Mmsystem.h>

#pragma comment(lib,"winmm.lib") //link lib

namespace music_player {
	class Music_Player {
	public:
		void Shoot_sound() {
			PlaySound(TEXT("E:\\switch\\program\\MUSIC\\shoot_ds.wav"), NULL, SND_FILENAME  | SND_ASYNC | SND_NOSTOP);
		}
		void Backgound_sound(bool on) {
			if (on)
			{
				mciSendString(TEXT("play E:\\switch\\program\\MUSIC\\background1_ds.mp3 repeat"), NULL, 0, NULL);
			}
			else
			{
				mciSendString(TEXT("close E:\\switch\\program\\MUSIC\\background1_ds.mp3"), NULL, 0, NULL);
			}
		};

		void Hit_sound() {
			PlaySound(TEXT("E:\\switch\\program\\MUSIC\\hit_ds.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
		};

		void Upgrade() {
			PlaySound(TEXT("E:\\switch\\program\\MUSIC\\upgrade_ds.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
		};

		void Game_over_sound() {
			PlaySound(TEXT("E:\\switch\\program\\MUSIC\\game_over_ds.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
		};

		void Achievement() {
			PlaySound(TEXT("E:\\switch\\program\\MUSIC\\achievement.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
		};



	};
}

