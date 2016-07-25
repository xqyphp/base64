#include "base64.h"


static const char* base_encode = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

static const char  base_decode[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	62, // '+'
	0, 0, 0,
	63, // '/'
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, // '0'-'9'
	0, 0, 0, 0, 0, 0, 0,
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
	13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, // 'A'-'Z'
	0, 0, 0, 0, 0, 0,
	26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
	39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, // 'a'-'z'
};

int encode_base64(const char* src, long len, char* out)
{
	long i = 0;
	long j = 0;

	for (i = 0; i < len - 2; i = i + 3){
		out[j++] = base_encode[(src[i] & 0xFC) >> 2];
		out[j++] = base_encode[((src[i] & 0x03) << 4) + ((src[i + 1] & 0xF0) >> 4)];
		out[j++] = base_encode[((src[i + 1] & 0x0F) << 2) + ((src[i + 2] & 0xc0) >> 6)];
		out[j++] = base_encode[src[i + 2] & 0x3f];
	}

	if (len % 3 == 1){
		out[j++] = base_encode[(src[i] & 0xFC) >> 2];
		out[j++] = base_encode[((src[i] & 0x03) << 4)];
		out[j++] = '=';
		out[j++] = '=';
	}
	else if (len % 3 == 2){
		out[j++] = base_encode[(src[i] & 0xFC) >> 2];
		out[j++] = base_encode[((src[i] & 0x03) << 4) + ((src[i + 1] & 0xF0) >> 4)];
		out[j++] = base_encode[((src[i + 1] & 0x0F) << 2)];
		out[j++] = '=';
	}
	out[j] = 0;
	return 1;
}

int decode_base64(const char* src, long len, char*out)
{
	long i = 0;
	long j = 0;

	for (i = 0; i < len - 3; i = i + 4){
		char i0 = base_decode[src[i]];
		char i1 = base_decode[src[i + 1]];
		char i2 = base_decode[src[i + 2]];
		char i3 = base_decode[src[i + 3]];
		if (src[i] == '=' || src[i + 1] == '=')
			break;
		out[j++] = ((i0 & 0x3F) << 2) + ((i1 & 0x30) >> 4);
		if (src[i + 2] == '=')
			break;
		out[j++] = ((i1 & 0x0F) << 4) + ((i2 & 0x3C) >> 2);
		if (src[i + 3] == '=')
			break;
		out[j++] = ((i2 & 0x03) << 6) + (i3 & 0x3F);

	}

	out[j] = 0;
	return j;
}
