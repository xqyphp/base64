#ifndef BASE_64_H
#ifdef __cplusplus
extern "C" {
#endif

static  long encode_len(long srclen)
{
	if (srclen < 0)return -1;
	return (srclen + 2) / 3 * 4 + 1;
}

static  long decode_len(long srclen)
{
	if (srclen < 0)return -1;
	return (srclen + 3) / 4 * 3 + 1;
}

int encode_base64(const char* src, long len, char* out);
int decode_base64(const char* src, long len, char*out);

#ifdef __cplusplus
}
#endif
#define BASE_64_H
#endif

