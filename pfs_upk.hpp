/*
This file is part of pfs_upk.

pfs_upk is free software: you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version. 

pfs_upk is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
pfs_upk. If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once
#include <cstring>
#include <string>

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#endif

#ifndef _WIN32
typedef char BYTE;
#define MAX_PATH 260
#endif // !_WIN32

const char ARCHIVE_MAGIC[] = {0x70, 0x66};
const char ARCHIVE_MAGIC_SIZE = sizeof(ARCHIVE_MAGIC);

struct Artemis_Entry {
#ifdef _WIN32
  std::wstring local_path;
#else
  std::string local_path;
#endif // _WIN32
  std::string path;
  char *position;
  uint32_t offset;
  uint32_t size;
};

#pragma pack(1)
struct Artemis_Header {
  char magic[ARCHIVE_MAGIC_SIZE];
  char pack_version;
  uint32_t index_size;
  uint32_t file_count;
};

bool pack(std::string path);
bool unpack(std::string path);
bool xorcrypt(char *text, uint32_t text_length, char *key, uint32_t key_length);

extern "C" {
#include "stdint.h"

typedef struct {
  uint32_t state[5];
  uint32_t count[2];
  unsigned char buffer[64];
} SHA1_CTX;

void SHA1Transform(uint32_t state[5], const unsigned char buffer[64]);

void SHA1Init(SHA1_CTX *context);

void SHA1Update(SHA1_CTX *context, const unsigned char *data, uint32_t len);

void SHA1Final(unsigned char digest[20], SHA1_CTX *context);

void SHA1(char *hash_out, const char *str, int len);
}