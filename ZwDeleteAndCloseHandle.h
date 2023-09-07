#pragma once
#include <stdlib.h>
#include <ntifs.h>
#include <ntstrsafe.h>
#include "NtHread.h"
#include "NtApi.h"
static unsigned char drmkaud[] = {

	0x4d, 0x5a, 0x90, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00,
	0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00,
	0x0e, 0x1f, 0xba, 0x0e, 0x00, 0xb4, 0x09, 0xcd, 0x21, 0xb8, 0x01, 0x4c, 0xcd, 0x21, 0x54, 0x68,
	0x69, 0x73, 0x20, 0x70, 0x72, 0x6f, 0x67, 0x72, 0x61, 0x6d, 0x20, 0x63, 0x61, 0x6e, 0x6e, 0x6f,
	0x74, 0x20, 0x62, 0x65, 0x20, 0x72, 0x75, 0x6e, 0x20, 0x69, 0x6e, 0x20, 0x44, 0x4f, 0x53, 0x20,
	0x6d, 0x6f, 0x64, 0x65, 0x2e, 0x0d, 0x0d, 0x0a, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xfd, 0xf2, 0x8b, 0xea, 0xb9, 0x93, 0xe5, 0xb9, 0xb9, 0x93, 0xe5, 0xb9, 0xb9, 0x93, 0xe5, 0xb9,
	0xb9, 0x93, 0xe4, 0xb9, 0xbc, 0x93, 0xe5, 0xb9, 0x7a, 0x9c, 0xb8, 0xb9, 0xbe, 0x93, 0xe5, 0xb9,
	0x7a, 0x9c, 0xba, 0xb9, 0xb8, 0x93, 0xe5, 0xb9, 0x7a, 0x9c, 0xbb, 0xb9, 0xb8, 0x93, 0xe5, 0xb9,
	0x7a, 0x9c, 0x85, 0xb9, 0xb8, 0x93, 0xe5, 0xb9, 0x7a, 0x9c, 0xbf, 0xb9, 0xb8, 0x93, 0xe5, 0xb9,
	0x52, 0x69, 0x63, 0x68, 0xb9, 0x93, 0xe5, 0xb9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x50, 0x45, 0x00, 0x00, 0x4c, 0x01, 0x07, 0x00, 0xb9, 0x54, 0x02, 0x48, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x0e, 0x01, 0x0b, 0x01, 0x07, 0x0a, 0x80, 0x02, 0x00, 0x00,
	0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x05, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00,
	0x80, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00,
	0x05, 0x00, 0x01, 0x00, 0x05, 0x00, 0x01, 0x00, 0x05, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x80, 0x0b, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x0d, 0x05, 0x01, 0x00, 0x01, 0x00, 0x00, 0x04,
	0x00, 0x00, 0x04, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x4c, 0x05, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x80, 0x06, 0x00, 0x00, 0x18, 0x04, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x0b, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0xa0, 0x03, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2e, 0x74, 0x65, 0x78, 0x74, 0x00, 0x00, 0x00,
	0x0c, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x68,
	0x2e, 0x72, 0x64, 0x61, 0x74, 0x61, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00,
	0x80, 0x00, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x48, 0x2e, 0x64, 0x61, 0x74, 0x61, 0x00, 0x00, 0x00,
	0x0c, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0xc8,
	0x50, 0x41, 0x47, 0x45, 0x00, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x80, 0x04, 0x00, 0x00,
	0x80, 0x00, 0x00, 0x00, 0x80, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x60, 0x49, 0x4e, 0x49, 0x54, 0x00, 0x00, 0x00, 0x00,
	0x12, 0x01, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0xe2,
	0x2e, 0x72, 0x73, 0x72, 0x63, 0x00, 0x00, 0x00, 0x18, 0x04, 0x00, 0x00, 0x80, 0x06, 0x00, 0x00,
	0x80, 0x04, 0x00, 0x00, 0x80, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x42, 0x2e, 0x72, 0x65, 0x6c, 0x6f, 0x63, 0x00, 0x00,
	0x2e, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x42,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x25, 0x80, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xee, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd0, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xb4, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xb9, 0x54, 0x02, 0x48, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
	0x24, 0x00, 0x00, 0x00, 0xcc, 0x03, 0x00, 0x00, 0xcc, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x08, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x52, 0x53, 0x44, 0x53,
	0x35, 0x4e, 0x23, 0xa6, 0x07, 0x7d, 0xe9, 0x43, 0x91, 0xc5, 0x00, 0x50, 0x97, 0x04, 0xc6, 0xf2,
	0x01, 0x00, 0x00, 0x00, 0x44, 0x72, 0x6d, 0x6b, 0x41, 0x75, 0x64, 0x2e, 0x70, 0x64, 0x62, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xbf, 0x44, 0xff, 0xff, 0x40, 0xbb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8b, 0xff, 0x55, 0x8b, 0xec, 0x51, 0x8d, 0x45, 0xfc, 0x50,
	0xe8, 0x71, 0xfe, 0xff, 0xff, 0x8b, 0x45, 0xfc, 0x68, 0xbc, 0x03, 0x01, 0x00, 0xff, 0x75, 0x0c,
	0xa3, 0x08, 0x04, 0x01, 0x00, 0xff, 0x75, 0x08, 0xff, 0x15, 0x88, 0x03, 0x01, 0x00, 0xc9, 0xc2,
	0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x8b, 0xff, 0x55, 0x8b, 0xec, 0xa1, 0x04, 0x04, 0x01, 0x00, 0x85,
	0xc0, 0xb9, 0x40, 0xbb, 0x00, 0x00, 0x74, 0x04, 0x3b, 0xc1, 0x75, 0x23, 0x8b, 0x15, 0x90, 0x03,
	0x01, 0x00, 0xb8, 0x04, 0x04, 0x01, 0x00, 0xc1, 0xe8, 0x08, 0x33, 0x02, 0x25, 0xff, 0xff, 0x00,
	0x00, 0xa3, 0x04, 0x04, 0x01, 0x00, 0x75, 0x07, 0x8b, 0xc1, 0xa3, 0x04, 0x04, 0x01, 0x00, 0xf7,
	0xd0, 0xa3, 0x00, 0x04, 0x01, 0x00, 0x5d, 0xe9, 0x3a, 0xff, 0xff, 0xff, 0xac, 0x05, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc2, 0x05, 0x00, 0x00, 0x90, 0x03, 0x00, 0x00,
	0xa4, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe6, 0x05, 0x00, 0x00,
	0x88, 0x03, 0x00, 0x00, 0x9c, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x08, 0x06, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xee, 0x05, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xd0, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb4, 0x05, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x66, 0x02, 0x4b, 0x65, 0x54, 0x69, 0x63, 0x6b, 0x43, 0x6f, 0x75, 0x6e,
	0x74, 0x00, 0x6e, 0x74, 0x6f, 0x73, 0x6b, 0x72, 0x6e, 0x6c, 0x2e, 0x65, 0x78, 0x65, 0x00, 0x00,
	0x79, 0x00, 0x4b, 0x73, 0x49, 0x6e, 0x69, 0x74, 0x69, 0x61, 0x6c, 0x69, 0x7a, 0x65, 0x44, 0x72,
	0x69, 0x76, 0x65, 0x72, 0x00, 0x00, 0x6b, 0x73, 0x2e, 0x73, 0x79, 0x73, 0x00, 0x00, 0x09, 0x00,
	0x44, 0x72, 0x6d, 0x47, 0x65, 0x74, 0x46, 0x69, 0x6c, 0x74, 0x65, 0x72, 0x44, 0x65, 0x73, 0x63,
	0x72, 0x69, 0x70, 0x74, 0x6f, 0x72, 0x00, 0x00, 0x64, 0x72, 0x6d, 0x6b, 0x2e, 0x73, 0x79, 0x73,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
	0x10, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x80,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
	0x09, 0x04, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0xe0, 0x06, 0x00, 0x00, 0xb4, 0x03, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xb4, 0x03, 0x34, 0x00, 0x00, 0x00, 0x56, 0x00, 0x53, 0x00, 0x5f, 0x00, 0x56, 0x00, 0x45, 0x00,
	0x52, 0x00, 0x53, 0x00, 0x49, 0x00, 0x4f, 0x00, 0x4e, 0x00, 0x5f, 0x00, 0x49, 0x00, 0x4e, 0x00,
	0x46, 0x00, 0x4f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbd, 0x04, 0xef, 0xfe, 0x00, 0x00, 0x01, 0x00,
	0x01, 0x00, 0x05, 0x00, 0x88, 0x15, 0x28, 0x0a, 0x01, 0x00, 0x05, 0x00, 0x88, 0x15, 0x28, 0x0a,
	0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x04, 0x00, 0x02, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x03, 0x00, 0x00,
	0x01, 0x00, 0x53, 0x00, 0x74, 0x00, 0x72, 0x00, 0x69, 0x00, 0x6e, 0x00, 0x67, 0x00, 0x46, 0x00,
	0x69, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x49, 0x00, 0x6e, 0x00, 0x66, 0x00, 0x6f, 0x00, 0x00, 0x00,
	0xf0, 0x02, 0x00, 0x00, 0x01, 0x00, 0x30, 0x00, 0x34, 0x00, 0x30, 0x00, 0x39, 0x00, 0x30, 0x00,
	0x34, 0x00, 0x42, 0x00, 0x30, 0x00, 0x00, 0x00, 0x4c, 0x00, 0x16, 0x00, 0x01, 0x00, 0x43, 0x00,
	0x6f, 0x00, 0x6d, 0x00, 0x70, 0x00, 0x61, 0x00, 0x6e, 0x00, 0x79, 0x00, 0x4e, 0x00, 0x61, 0x00,
	0x6d, 0x00, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4d, 0x00, 0x69, 0x00, 0x63, 0x00, 0x72, 0x00,
	0x6f, 0x00, 0x73, 0x00, 0x6f, 0x00, 0x66, 0x00, 0x74, 0x00, 0x20, 0x00, 0x43, 0x00, 0x6f, 0x00,
	0x72, 0x00, 0x70, 0x00, 0x6f, 0x00, 0x72, 0x00, 0x61, 0x00, 0x74, 0x00, 0x69, 0x00, 0x6f, 0x00,
	0x6e, 0x00, 0x00, 0x00, 0x84, 0x00, 0x2e, 0x00, 0x01, 0x00, 0x46, 0x00, 0x69, 0x00, 0x6c, 0x00,
	0x65, 0x00, 0x44, 0x00, 0x65, 0x00, 0x73, 0x00, 0x63, 0x00, 0x72, 0x00, 0x69, 0x00, 0x70, 0x00,
	0x74, 0x00, 0x69, 0x00, 0x6f, 0x00, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4d, 0x00, 0x69, 0x00,
	0x63, 0x00, 0x72, 0x00, 0x6f, 0x00, 0x73, 0x00, 0x6f, 0x00, 0x66, 0x00, 0x74, 0x00, 0x20, 0x00,
	0x4b, 0x00, 0x65, 0x00, 0x72, 0x00, 0x6e, 0x00, 0x65, 0x00, 0x6c, 0x00, 0x20, 0x00, 0x44, 0x00,
	0x52, 0x00, 0x4d, 0x00, 0x20, 0x00, 0x41, 0x00, 0x75, 0x00, 0x64, 0x00, 0x69, 0x00, 0x6f, 0x00,
	0x20, 0x00, 0x44, 0x00, 0x65, 0x00, 0x73, 0x00, 0x63, 0x00, 0x72, 0x00, 0x61, 0x00, 0x6d, 0x00,
	0x62, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x72, 0x00, 0x20, 0x00, 0x46, 0x00, 0x69, 0x00, 0x6c, 0x00,
	0x74, 0x00, 0x65, 0x00, 0x72, 0x00, 0x00, 0x00, 0x62, 0x00, 0x21, 0x00, 0x01, 0x00, 0x46, 0x00,
	0x69, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x56, 0x00, 0x65, 0x00, 0x72, 0x00, 0x73, 0x00, 0x69, 0x00,
	0x6f, 0x00, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x35, 0x00, 0x2e, 0x00, 0x31, 0x00, 0x2e, 0x00,
	0x32, 0x00, 0x36, 0x00, 0x30, 0x00, 0x30, 0x00, 0x2e, 0x00, 0x35, 0x00, 0x35, 0x00, 0x31, 0x00,
	0x32, 0x00, 0x20, 0x00, 0x28, 0x00, 0x78, 0x00, 0x70, 0x00, 0x73, 0x00, 0x70, 0x00, 0x2e, 0x00,
	0x30, 0x00, 0x38, 0x00, 0x30, 0x00, 0x34, 0x00, 0x31, 0x00, 0x33, 0x00, 0x2d, 0x00, 0x32, 0x00,
	0x31, 0x00, 0x30, 0x00, 0x38, 0x00, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x0c, 0x00,
	0x01, 0x00, 0x49, 0x00, 0x6e, 0x00, 0x74, 0x00, 0x65, 0x00, 0x72, 0x00, 0x6e, 0x00, 0x61, 0x00,
	0x6c, 0x00, 0x4e, 0x00, 0x61, 0x00, 0x6d, 0x00, 0x65, 0x00, 0x00, 0x00, 0x64, 0x00, 0x72, 0x00,
	0x6d, 0x00, 0x6b, 0x00, 0x61, 0x00, 0x75, 0x00, 0x64, 0x00, 0x2e, 0x00, 0x73, 0x00, 0x79, 0x00,
	0x73, 0x00, 0x00, 0x00, 0x80, 0x00, 0x2e, 0x00, 0x01, 0x00, 0x4c, 0x00, 0x65, 0x00, 0x67, 0x00,
	0x61, 0x00, 0x6c, 0x00, 0x43, 0x00, 0x6f, 0x00, 0x70, 0x00, 0x79, 0x00, 0x72, 0x00, 0x69, 0x00,
	0x67, 0x00, 0x68, 0x00, 0x74, 0x00, 0x00, 0x00, 0xa9, 0x00, 0x20, 0x00, 0x4d, 0x00, 0x69, 0x00,
	0x63, 0x00, 0x72, 0x00, 0x6f, 0x00, 0x73, 0x00, 0x6f, 0x00, 0x66, 0x00, 0x74, 0x00, 0x20, 0x00,
	0x43, 0x00, 0x6f, 0x00, 0x72, 0x00, 0x70, 0x00, 0x6f, 0x00, 0x72, 0x00, 0x61, 0x00, 0x74, 0x00,
	0x69, 0x00, 0x6f, 0x00, 0x6e, 0x00, 0x2e, 0x00, 0x20, 0x00, 0x41, 0x00, 0x6c, 0x00, 0x6c, 0x00,
	0x20, 0x00, 0x72, 0x00, 0x69, 0x00, 0x67, 0x00, 0x68, 0x00, 0x74, 0x00, 0x73, 0x00, 0x20, 0x00,
	0x72, 0x00, 0x65, 0x00, 0x73, 0x00, 0x65, 0x00, 0x72, 0x00, 0x76, 0x00, 0x65, 0x00, 0x64, 0x00,
	0x2e, 0x00, 0x00, 0x00, 0x40, 0x00, 0x0c, 0x00, 0x01, 0x00, 0x4f, 0x00, 0x72, 0x00, 0x69, 0x00,
	0x67, 0x00, 0x69, 0x00, 0x6e, 0x00, 0x61, 0x00, 0x6c, 0x00, 0x46, 0x00, 0x69, 0x00, 0x6c, 0x00,
	0x65, 0x00, 0x6e, 0x00, 0x61, 0x00, 0x6d, 0x00, 0x65, 0x00, 0x00, 0x00, 0x64, 0x00, 0x72, 0x00,
	0x6d, 0x00, 0x6b, 0x00, 0x61, 0x00, 0x75, 0x00, 0x64, 0x00, 0x2e, 0x00, 0x73, 0x00, 0x79, 0x00,
	0x73, 0x00, 0x00, 0x00, 0x6a, 0x00, 0x25, 0x00, 0x01, 0x00, 0x50, 0x00, 0x72, 0x00, 0x6f, 0x00,
	0x64, 0x00, 0x75, 0x00, 0x63, 0x00, 0x74, 0x00, 0x4e, 0x00, 0x61, 0x00, 0x6d, 0x00, 0x65, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x4d, 0x00, 0x69, 0x00, 0x63, 0x00, 0x72, 0x00, 0x6f, 0x00, 0x73, 0x00,
	0x6f, 0x00, 0x66, 0x00, 0x74, 0x00, 0xae, 0x00, 0x20, 0x00, 0x57, 0x00, 0x69, 0x00, 0x6e, 0x00,
	0x64, 0x00, 0x6f, 0x00, 0x77, 0x00, 0x73, 0x00, 0xae, 0x00, 0x20, 0x00, 0x4f, 0x00, 0x70, 0x00,
	0x65, 0x00, 0x72, 0x00, 0x61, 0x00, 0x74, 0x00, 0x69, 0x00, 0x6e, 0x00, 0x67, 0x00, 0x20, 0x00,
	0x53, 0x00, 0x79, 0x00, 0x73, 0x00, 0x74, 0x00, 0x65, 0x00, 0x6d, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x40, 0x00, 0x0e, 0x00, 0x01, 0x00, 0x50, 0x00, 0x72, 0x00, 0x6f, 0x00, 0x64, 0x00, 0x75, 0x00,
	0x63, 0x00, 0x74, 0x00, 0x56, 0x00, 0x65, 0x00, 0x72, 0x00, 0x73, 0x00, 0x69, 0x00, 0x6f, 0x00,
	0x6e, 0x00, 0x00, 0x00, 0x35, 0x00, 0x2e, 0x00, 0x31, 0x00, 0x2e, 0x00, 0x32, 0x00, 0x36, 0x00,
	0x30, 0x00, 0x30, 0x00, 0x2e, 0x00, 0x35, 0x00, 0x35, 0x00, 0x31, 0x00, 0x32, 0x00, 0x00, 0x00,
	0x44, 0x00, 0x00, 0x00, 0x01, 0x00, 0x56, 0x00, 0x61, 0x00, 0x72, 0x00, 0x46, 0x00, 0x69, 0x00,
	0x6c, 0x00, 0x65, 0x00, 0x49, 0x00, 0x6e, 0x00, 0x66, 0x00, 0x6f, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x24, 0x00, 0x04, 0x00, 0x00, 0x00, 0x54, 0x00, 0x72, 0x00, 0x61, 0x00, 0x6e, 0x00, 0x73, 0x00,
	0x6c, 0x00, 0x61, 0x00, 0x74, 0x00, 0x69, 0x00, 0x6f, 0x00, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x09, 0x04, 0xb0, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x08, 0x33, 0xc4, 0x33, 0x99, 0x34, 0xa1, 0x34,
	0xaa, 0x34, 0x0b, 0x35, 0x1e, 0x35, 0x23, 0x35, 0x32, 0x35, 0x3b, 0x35, 0x42, 0x35, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
#pragma pack(8) //�ñ�����������ṹ��8�ֽڶ���




/*---------------------------------------------------------------------------*/


/*----------------------------------------------*/


BOOLEAN
IsFile(
	PVOID Object);


NTSTATUS
IrpSetInformationFileCompletionRoutine(
	PDEVICE_OBJECT device,
	PIRP aIrp,
	PVOID context);


NTSTATUS
IrpSetInformationFile(
	PFILE_OBJECT            aFileObject,
	PIO_STATUS_BLOCK        aIoStatusBlock,
	PVOID                   aFileInformation,
	ULONG                   aLength,
	FILE_INFORMATION_CLASS  aFileInformationClass);


NTSTATUS
FixFilePath(
	PWCHAR* aFixedPath,
	PWCHAR aFilePath);


NTSTATUS
DeleteFileWithIrp(
	PWCHAR aFilePath);


NTSTATUS
GetFullPathName(
	PFILE_OBJECT fileObject,
	POBJECT_NAME_INFORMATION *objectNameInformation);


PMY_SYSTEM_HANDLE_INFORMATION
EnumerateHandles();


VOID
R0_CloseAllHandles(
	PWCHAR FilePath);

NTSTATUS
DeleteMySelf(
	PUNICODE_STRING reg_path);

/*--------------------------------------------------------*/