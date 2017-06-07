#include "Base64.h"

const char b64_alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";

/* 'Private' declarations */
inline void a3_to_a4(unsigned char * a4, unsigned char * a3);
inline void a4_to_a3(unsigned char * a3, unsigned char * a4);
//inline void a2_to_a3(unsigned char * a3, unsigned char * a2);
//inline void a1_to_a3(unsigned char * a3, unsigned char * a1);
//inline void a1_to_a6(unsigned char * a6, unsigned char * a1);
inline unsigned char b64_lookup(char c);

int base64_encode(char *output, char *input, int inputLen) {
	int i = 0, j = 0;
	int encLen = 0;
	unsigned char a3[3];
	unsigned char a4[4];

	while(inputLen--) {
		a3[i++] = *(input++);
		if(i == 3) {
			a3_to_a4(a4, a3);

			for(i = 0; i < 4; i++) {
				output[encLen++] = b64_alphabet[a4[i]];
			}

			i = 0;
		}
	}

	if(i) {
		for(j = i; j < 3; j++) {
			a3[j] = '\0';
		}

		a3_to_a4(a4, a3);

		for(j = 0; j < i + 1; j++) {
			output[encLen++] = b64_alphabet[a4[j]];
		}

		while((i++ < 3)) {
			output[encLen++] = '=';
		}
	}
	output[encLen] = '\0';
	return encLen;
}

int base64_decode(unsigned char * output, char * input, int inputLen) {
	int i = 0, j = 0;
	int decLen = 0;
	unsigned char a3[3];
	unsigned char a4[4];


	while (inputLen--) {
		if(*input == '=') {
			break;
		}

		a4[i++] = *(input++);
		if (i == 4) {
			for (i = 0; i <4; i++) {
				a4[i] = b64_lookup(a4[i]);
			}

			a4_to_a3(a3,a4);

			for (i = 0; i < 3; i++) {
				output[decLen++] = a3[i];
			}
			i = 0;
		}
	}

	if (i) {
		for (j = i; j < 4; j++) {
			a4[j] = '\0';
		}

		for (j = 0; j <4; j++) {
			a4[j] = b64_lookup(a4[j]);
		}

		a4_to_a3(a3,a4);

		for (j = 0; j < i - 1; j++) {
			output[decLen++] = a3[j];
		}
	}
	output[decLen] = '\0';
	return decLen;
}

/*int base64_decode4bit(unsigned char * output, char * input, int inputLen) {
  int i = 0, j = 0;
  int decLen = 0;
  unsigned char a3[3]; // Byte output (Only 0,17,34,51,....,238,255 is returned)
  unsigned char a2[2]; // Base64 Input


  while (inputLen--) {
    if(*input == '=') {
      break;
    }

    a2[i++] = *(input++);
    if (i == 2) {
      for (i = 0; i <2; i++) {
        a2[i] = b64_lookup(a2[i]);
      }

      a2_to_a3(a3,a2);

      for (i = 0; i < 3; i++) {
        output[decLen++] = a3[i];
      }
      i = 0;
    }
  }

  if (i) {
    for (j = i; j < 2; j++) {
      a2[j] = '\0';
    }

    for (j = 0; j <2; j++) {
      a2[j] = b64_lookup(a2[j]);
    }

    a2_to_a3(a3,a2);

    for (j = 0; j < i - 1; j++) {
      output[decLen++] = a3[j];
    }
  }
  output[decLen] = '\0';
  return decLen;
}

int base64_decode2bit(unsigned char * output, char * input, int inputLen) {
  int i = 0, j = 0;
  int decLen = 0;
  unsigned char a3[3]; // Byte output (Only 0,85,170 or 255 is returned)
  unsigned char a1[1]; // Base64 Input


  while (inputLen--) {
    if(*input == '=') {
      break;
    }

    a1[i++] = *(input++);
    if (i == 1) {
      for (i = 0; i <1; i++) {
        a1[i] = b64_lookup(a1[i]);
      }

      a1_to_a3(a3,a1);

      for (i = 0; i < 3; i++) {
        output[decLen++] = a3[i];
      }
      i = 0;
    }
  }

  if (i) {
    for (j = i; j < 1; j++) {
      a1[j] = '\0';
    }

    for (j = 0; j <1; j++) {
      a1[j] = b64_lookup(a1[j]);
    }

    a1_to_a3(a3,a1);

    for (j = 0; j < i - 1; j++) {
      output[decLen++] = a3[j];
    }
  }
  output[decLen] = '\0';
  return decLen;
}

int base64_decode1bit(unsigned char * output, char * input, int inputLen) {
  int i = 0, j = 0;
  int decLen = 0;
  unsigned char a6[6]; // Byte output (Only 0 or 255 is returned)
  unsigned char a1[1]; // Base64 Input


  while (inputLen--) {
    if(*input == '=') {
      break;
    }

    a1[i++] = *(input++);
    if (i == 1) {
      for (i = 0; i <1; i++) {
        a1[i] = b64_lookup(a1[i]);
      }

      a1_to_a6(a6,a1);

      for (i = 0; i < 6; i++) {
        output[decLen++] = a6[i];
      }
      i = 0;
    }
  }

  if (i) {
    for (j = i; j < 1; j++) {
      a1[j] = '\0';
    }

    for (j = 0; j <1; j++) {
      a1[j] = b64_lookup(a1[j]);
    }

    a1_to_a6(a6,a1);

    for (j = 0; j < i - 1; j++) {
      output[decLen++] = a6[j];
    }
  }
  output[decLen] = '\0';
  return decLen;
}
*/
int base64_enc_len(int plainLen) {
	int n = plainLen;
	return (n + 2 - ((n + 2) % 3)) / 3 * 4;
}

int base64_dec_len(char * input, int inputLen) {
	int i = 0;
	int numEq = 0;
	for(i = inputLen - 1; input[i] == '='; i--) {
		numEq++;
	}

	return ((6 * inputLen) / 8) - numEq;
}
/*
int base64_dec_len1bit(char * input, int inputLen) {
  int i = 0;
  int numEq = 0;
  for(i = inputLen - 1; input[i] == '='; i--) {
    numEq++;
  }

  return (6 * inputLen) - numEq;
}

int base64_dec_len2bit(char * input, int inputLen) {
  int i = 0;
  int numEq = 0;
  for(i = inputLen - 1; input[i] == '='; i--) {
    numEq++;
  }

  return ((6 * inputLen) / 2) - numEq;
}

int base64_dec_len4bit(char * input, int inputLen) {
  int i = 0;
  int numEq = 0;
  for(i = inputLen - 1; input[i] == '='; i--) {
    numEq++;
  }

  return ((6 * inputLen) / 4) - numEq;
}
*/
inline void a3_to_a4(unsigned char * a4, unsigned char * a3) {
	a4[0] = (a3[0] & 0xfc) >> 2;
	a4[1] = ((a3[0] & 0x03) << 4) + ((a3[1] & 0xf0) >> 4);
	a4[2] = ((a3[1] & 0x0f) << 2) + ((a3[2] & 0xc0) >> 6);
	a4[3] = (a3[2] & 0x3f);
}

inline void a4_to_a3(unsigned char * a3, unsigned char * a4) { // 8 bit pixels. 0=0, 1=1, 255=255
	a3[0] = (a4[0] << 2) + ((a4[1] & 0x30) >> 4);
	a3[1] = ((a4[1] & 0xf) << 4) + ((a4[2] & 0x3c) >> 2);
	a3[2] = ((a4[2] & 0x3) << 6) + a4[3];
}
/*
inline void a2_to_a3(unsigned char * a3, unsigned char * a2) { // 4 bit pixels. 0=0, 1=17, 7=119, 15=255
  a3[0] = ((a2[0] & 0x3c) >> 2) * 17;
  a3[1] = (((a2[0] & 0x3) << 2) + ((a2[1] & 0x3c) >> 2))  * 17;
  a3[2] = (a2[1] & 0xf) * 17;
}

inline void a1_to_a3(unsigned char * a3, unsigned char * a1) { // 2 bit pixels. 0=0, 1=85, 2=170, 3=255
  a3[0] = ((a1[0] & 0x30) >> 4) * 85;
  a3[1] = ((a1[0] & 0xc) >> 2) * 85;
  a3[2] = (a1[0] & 0x3) * 85;
}

inline void a1_to_a6(unsigned char * a6, unsigned char * a1) { // 1 bit pixels. 0=0, 1=255
  a6[0] = ((a1[0] & 0x20) >> 5) * 255;
  a6[1] = ((a1[0] & 0x10) >> 4) * 255;
  a6[2] = ((a1[0] & 0x8) >> 3) * 255;
  a6[3] = ((a1[0] & 0x4) >> 2) * 255;
  a6[4] = ((a1[0] & 0x2) >> 1) * 255;
  a6[5] = ((a1[0] & 0x1)) * 255;
}
*/
/*inline void a1_to_a16(unsigned char * a16, unsigned char * a1) {
  byte v1 = (a1[0] & 0x38) >> 3;
  byte v2 = (a1[0] & 0x7);
  for (int i = 0; i < 8; i++) {
    a16[i]  = (v1 > i ? 255 : 0);
  }
  for (int i = 0; i < 8; i++) {
    a16[i+8]  = (v2 > i ? 255 : 0);
  }
}*/

inline unsigned char b64_lookup(char c) {
	if(c >='A' && c <='Z') return c - 'A';
	if(c >='a' && c <='z') return c - 71;
	if(c >='0' && c <='9') return c + 4;
	if(c == '+') return 62;
	if(c == '/') return 63;
	return -1;
}
