#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/soundcard.h>

// Hardcoded audio file path
#define AUDIO_PATH "/home/magno/googleDrive/Minhas_Tralhas/Aulas/HEMU/gitWorkshopsHEMU/assets/notaPiano.wav"
#define BUFFER_SIZE 4096

// WAV header structure
typedef struct {
    char     chunk_id[4];     // "RIFF"
    uint32_t chunk_size;
    char     format[4];       // "WAVE"
    char     subchunk1_id[4]; // "fmt "
    uint32_t subchunk1_size;
    uint16_t audio_format;    // 1 = PCM
    uint16_t num_channels;    // 1 = Mono, 2 = Stereo
    uint32_t sample_rate;     // e.g., 44100
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bits_per_sample; // e.g., 16
    char     subchunk2_id[4]; // "data"
    uint32_t subchunk2_size;  // Size of audio data
} WavHeader;

int main(void) {
    // 1. Open audio file
    int audio_fd = open(AUDIO_PATH, O_RDONLY);
    if (audio_fd < 0) {
        perror("Failed to open audio file");
        return EXIT_FAILURE;
    }

    // 2. Read WAV header
    WavHeader header;
    if (read(audio_fd, &header, sizeof(WavHeader)) != sizeof(WavHeader)) {
        fprintf(stderr, "Failed to read WAV header\n");
        close(audio_fd);
        return EXIT_FAILURE;
    }

    // Basic validation
    if (header.chunk_id[0] != 'R' || header.chunk_id[1] != 'I' ||
        header.chunk_id[2] != 'F' || header.chunk_id[3] != 'F') {
        fprintf(stderr, "Error: File is not a valid RIFF WAV file\n");
        close(audio_fd);
        return EXIT_FAILURE;
    }

    // 3. Open sound device
    int dsp_fd = open("/dev/dsp", O_WRONLY);
    if (dsp_fd < 0) {
        perror("Failed to open /dev/dsp");
        close(audio_fd);
        return EXIT_FAILURE;
    }

    // 4. Configure audio hardware settings
    int format = (header.bits_per_sample == 8) ? AFMT_U8 : AFMT_S16_LE;
    int channels = header.num_channels;
    int speed = header.sample_rate;

    if (ioctl(dsp_fd, SOUND_PCM_SETFMT, &format) == -1 ||
        ioctl(dsp_fd, SOUND_PCM_WRITE_CHANNELS, &channels) == -1 ||
        ioctl(dsp_fd, SOUND_PCM_WRITE_RATE, &speed) == -1) {
        perror("Failed to configure audio device");
        close(audio_fd);
        close(dsp_fd);
        return EXIT_FAILURE;
    }
    printf("Playing %s (%u Hz, %u-bit, %u channel(s))...\n",
           AUDIO_PATH, speed, header.bits_per_sample, channels);

    // 5. Stream audio buffer
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(audio_fd, buffer, sizeof(buffer))) > 0) {
        ssize_t bytes_written = 0;
        while (bytes_written < bytes_read) {
            ssize_t res = write(dsp_fd, buffer + bytes_written, bytes_read - bytes_written);
            if (res <= 0) {
                perror("Write error to audio device");
                break;
            }
            bytes_written += res;
        }
    }

    close(audio_fd);
    close(dsp_fd);

    printf("Finished playback.\n");
    return EXIT_SUCCESS;
}
