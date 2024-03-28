#include "SoundManager.h"
#include  <iostream>

enum sound_type
{
	NONE = -1,
	MUSIC_SOUND = 0,
	SOUND_EFFECT = 1
};

SoundManager* SoundManager::s_pInstance = nullptr;

SoundManager::SoundManager()
{
	//Tần số(Frequency) : Tham số này chỉ định tần số lấy mẫu đầu ra tính bằng số lần lấy mẫu mỗi giây(Hz).
	// Ví dụ, giá trị 22050 thường được sử dụng trong các trò chơi vì 44100 (tần số của CD âm thanh) 
	// đòi hỏi nhiều sức mạnh CPU hơn trên các máy tính cũ.
	//Định dạng(Format) : Định dạng âm thanh được chỉ định bằng một trong các hằng số AUDIO_ * của SDL.
	// Định dạng thông dụng bao gồm :
	//AUDIO_S16SYS: Đại diện cho âm thanh 16 - bit và là một lựa chọn an toàn.
	//AUDIO_F32SYS : Được sử dụng cho âm thanh dạng số dấu phẩy động 32 - bit(trên các hệ thống hiện đại).
	//Kênh(Channels) : Tham số này chỉ ra số lượng kênh :
	//1 : Đầu ra mono.
	//2 : Đầu ra stereo.
	//Đối với cấu hình âm thanh vòm, bạn có thể thử nghiệm với 4 (quad), 6 (5.1), 7 (6.1), hoặc 8 (7.1) kênh.
	//Kích thước Khối(Chunk Size) : Kích thước khối đại diện cho số khung mẫu được cấp cho thiết bị 
	//cùng một lúc.Giá trị thấp giảm độ trễ nhưng có thể gây ra sự gián đoạn.Một giá trị mặc định thông thường là 2048.
	Mix_OpenAudio(22050, AUDIO_S16, 2, 2048);
}

bool SoundManager::loadSound(std::string fileName, std::string id, sound_type type)
{
	if (type == MUSIC_SOUND)
	{
		Mix_Music* pMUSIC_SOUND = Mix_LoadMUS(fileName.c_str());

		if (pMUSIC_SOUND == 0)
		{
			std::cout << "Could not load MUSIC_SOUND\n";

			return false;
		}

		mMusic[id] = pMUSIC_SOUND;
		return true;
	}
	else if (type == SOUND_EFFECT)
	{
		Mix_Chunk* pChunk = Mix_LoadWAV(fileName.c_str());

		if (pChunk == 0)
		{
			std::cout << "Could not load SOUND_EFFECT\n";

			return false;
		}
		mSfxs[id] = pChunk;
		return true;
	}

	return false;
}

void SoundManager::playMusic(std::string id, int loop)
{
	//Hàm Mix_PlayMUSIC_SOUND được sử dụng để phát một đối tượng âm nhạc mới.
	Mix_PlayMusic(mMusic[id], loop);
}

void SoundManager::playSound(std::string id, int loop, int channel)
{
	//Hàm Mix_PlayChannel trong SDL_mixer cho phép bạn phát một đoạn âm thanh(chunk) trên một kênh cụ thể
	Mix_PlayChannel(channel, mSfxs[id], loop);
}

SoundManager::~SoundManager()
{
	Mix_CloseAudio();
}