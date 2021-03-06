#ifndef INLINE_UTILS_HPP
# define INLINE_UTILS_HPP

#include <cstdint>

inline uint32_t endian_conv_32(uint32_t in)
{
	return (in >> 24) | (0xff00 & (in >> 8)) | (0xff0000 & (in << 8)) | (in << 24);
}

#endif
