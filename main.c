//Copyright 2021-2022 Raducanu George-Cristian 311CAb
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

typedef struct head {
	unsigned char type;
	unsigned int len;
} head;

typedef struct data_structure {
	head *header;
	void *data;
} data_structure;


//function for counting the number of bytes in arr generic vector
int size_arr(void *arr, int len)
{
	int c = 0;
	unsigned int x;
	unsigned int *p;
	unsigned char *v = (unsigned char *)arr;
	for (int i = 0; i < len; ++i) {
		c += sizeof(unsigned char);
		c += sizeof(unsigned int);
		v += sizeof(unsigned char);
		p = (unsigned int *)v;
		x = *p;
		c += x;
		v += sizeof(unsigned int);
		v += x;
	}
	return c;
}

int add_last(void **arr, int *len, data_structure *data)
{
	unsigned char *v;
	if (*len != 0) {
		int tot = size_arr(*arr, *len);
		*arr = realloc(*arr, tot + sizeof(unsigned char) + sizeof(unsigned int) + data->header->len);
		if (*arr == NULL)
			return -1;
		v = (unsigned char *)(*arr);
		v += tot;
	} else {
		*arr = malloc(sizeof(unsigned char) + sizeof(unsigned int) + data->header->len);
		if (*arr == NULL)
			return -1;
		v = (unsigned char *)(*arr);
	}
	memcpy(v, &(data->header->type), sizeof(unsigned char));
	memcpy(v + sizeof(unsigned char), &(data->header->len), sizeof(unsigned int));
	memcpy(v + sizeof(unsigned char) + sizeof(unsigned int), data->data, data->header->len);
	++(*len);
	return 1;
}

int add_at(void **arr, int *len, data_structure *data, int index)
{
	unsigned char *v;
	unsigned int count = 0;
	int tot = size_arr(*arr, *len);
	if (index < 0)
		return -1;
	if (index >= *len)
		index = *len;
	*arr = realloc(*arr, tot + sizeof(unsigned char) + sizeof(unsigned int) + data->header->len);
	if (*arr == NULL)
		return -1;
	v = (unsigned char *)(*arr);
	for (int i = 0; i < index; ++i) {
		v += sizeof(unsigned char);
		unsigned int l, *ll;
		ll = (unsigned int *)v;
		l = *ll;
		count += (l + sizeof(unsigned char) + sizeof(unsigned int));
		v += sizeof(unsigned int);
		v += l;
	}
	unsigned int dif = tot - count;
	memcpy(v + sizeof(unsigned char) + sizeof(unsigned int) + data->header->len, v, dif);
	memcpy(v, &(data->header->type), sizeof(unsigned char));
	memcpy(v + sizeof(unsigned char), &(data->header->len), sizeof(unsigned int));
	memcpy(v + sizeof(unsigned char) + sizeof(unsigned int), data->data, data->header->len);
	++(*len);
	return 0;
}

void find(void *data_block, int len, int index) 
{
	if (index < 0 || index >= len)
		return;
	unsigned char *v = (unsigned char *)(data_block);
	for (int i = 0; i < index; ++i) {
		v += sizeof(unsigned char);
		unsigned int l, *ll;
		ll = (unsigned int *)v;
		l = *ll;
		v += sizeof(unsigned int);
		v += l;
	}
	unsigned char c, *cc;
	cc = (unsigned char *)v;
	c = *cc;
	printf("Tipul %c\n", c);
	v += sizeof(unsigned char);
	v += sizeof(unsigned int);
	unsigned char *nume1 = v;
	printf("%s ", nume1);
	v += (strlen((char *)nume1) + 1) * sizeof(unsigned char);
	printf ("pentru ");
	if (c == '1') {
		int8_t a, *aa;
		int8_t b, *bb;
		aa = (int8_t *)v;
		a = *aa;
		v += sizeof(int8_t);
		bb = (int8_t *)v;
		b = *bb;
		v += sizeof(int8_t);
		unsigned char *nume2 = v;
		printf("%s\n", nume2);
		v += (strlen((char *)nume2) + 1) * sizeof(unsigned char);
		printf("%"PRId8"\n", a);
		printf("%"PRId8"\n", b);
		printf("\n");
	}
	if (c == '2') {
		int16_t a, *aa;
		int32_t b, *bb;
		aa = (int16_t *)v;
		a = *aa;
		v += sizeof(int16_t);
		bb = (int32_t *)v;
		b = *bb;
		v += sizeof(int32_t);
		unsigned char *nume2 = v;
		printf("%s\n", nume2);
		v += (strlen((char *)nume2) + 1) * sizeof(unsigned char);
		printf("%"PRId16"\n", a);
		printf("%"PRId32"\n", b);
		printf("\n");
	}
	if (c == '3') {
		int32_t a, *aa;
		int32_t b, *bb;
		aa = (int32_t *)v;
		a = *aa;
		v += sizeof(int32_t);
		bb = (int32_t *)v;
		b = *bb;
		v += sizeof(int32_t);
		unsigned char *nume2 = v;
		printf("%s\n", nume2);
		v += (strlen((char *)nume2) + 1) * sizeof(unsigned char);
		printf("%"PRId32"\n", a);
		printf("%"PRId32"\n", b);
		printf("\n");
	}
}

int delete_at(void **arr, int *len, int index)
{
	if (index < 0 || index >= *len)
		return -1;
	unsigned int count = 0;
	unsigned char *v = (unsigned char *)(*arr);
	for (int i = 0; i < index; ++i) {
		v += sizeof(unsigned char);
		unsigned int l, *ll;
		ll = (unsigned int *)v;
		l = *ll;
		count += (l + sizeof(unsigned char) + sizeof(unsigned int));
		v += sizeof(unsigned int);
		v += l;
		l = 0; // for eliminating warning 
	}
	int tot = size_arr(*arr, *len);
	unsigned int j, *jj;
	jj = (unsigned int *)(v + sizeof(unsigned char));
	j = *jj;
	memcpy(v, v + sizeof(unsigned char) + sizeof(unsigned int) + j, tot - count - j - sizeof(unsigned char) - sizeof(unsigned int));
	tot -= (sizeof(unsigned char) + sizeof(unsigned int) + j);
	--(*len);
	*arr = realloc(*arr, tot);
	return 1;	
}

void print(void *arr, int len)
{
	unsigned char *v = (unsigned char *)arr;
	for (int i = 0; i < len; ++i) {
		unsigned char c, *cc;
		cc = (unsigned char *)v;
		c = *cc;
		v += sizeof(unsigned char);
		v += sizeof(unsigned int);
		printf("Tipul %c\n", c);
		unsigned char *nume1 = v;
		printf("%s ", nume1);
		v += (1 + strlen((char *)nume1))*sizeof(unsigned char);
		printf("pentru ");
		if (c == '1') {
		int8_t a, *aa;
		int8_t b, *bb;
		aa = (int8_t *)v;
		a = *aa;
		v += sizeof(int8_t);
		bb = (int8_t *)v;
		b = *bb;
		v += sizeof(int8_t);
		unsigned char *nume2 = v;
		printf("%s\n", nume2);
		v += (strlen((char *)nume2) + 1) * sizeof(unsigned char);
		printf("%"PRId8"\n", a);
		printf("%"PRId8"\n", b);
		printf("\n");
	}
	if (c == '2') {
		int16_t a, *aa;
		int32_t b, *bb;
		aa = (int16_t *)v;
		a = *aa;
		v += sizeof(int16_t);
		bb = (int32_t *)v;
		b = *bb;
		v += sizeof(int32_t);
		unsigned char *nume2 = v;
		printf("%s\n", nume2);
		v += (strlen((char *)nume2) + 1) * sizeof(unsigned char);
		printf("%"PRId16"\n", a);
		printf("%"PRId32"\n", b);
		printf("\n");
	}
	if (c == '3') {
		int32_t a, *aa;
		int32_t b, *bb;
		aa = (int32_t *)v;
		a = *aa;
		v += sizeof(int32_t);
		bb = (int32_t *)v;
		b = *bb;
		v += sizeof(int32_t);
		unsigned char *nume2 = v;
		printf("%s\n", nume2);
		v += (strlen((char *)nume2) + 1) * sizeof(unsigned char);
		printf("%"PRId32"\n", a);
		printf("%"PRId32"\n", b);
		printf("\n");
	}
	}
}

int verif_comm(char *s)
{
	if (strstr(s, "insert_at"))
		return 1;
	if (strstr(s, "insert"))
		return 2;
	if (strstr(s, "delete_at"))
		return 3;
	if (strstr(s, "find"))
		return 4;
	if (strstr(s, "print"))
		return 5;
	if (strstr(s, "exit"))
		return 6;
	return -1;
}

//the main function that will help "Florin Copilu' de Biti"
int main() {
	// the vector of bytes u have to work with
	// good luck :)
	void *arr = NULL;
	int len = 0;
	char comm[256];
	int ready = 0;
	while (ready == 0) {
		fgets(comm, 256, stdin);
		comm[strlen(comm) - 1] = '\0';
		int co = verif_comm(comm);
		if (co == 1) {
			int index, nr = 0;
			char *nume1, *nume2, tip, *p;
			int8_t b1_8, b2_8;
			int16_t b1_16;
			int32_t b1_32, b2_32;
			p = strtok(comm, " ");
			while (p) {
				if (nr == 1) {
					index = (int)atoi(p);
				}
				if (nr == 2) {
					tip = p[0];
				}
				if (nr == 3) {
					nume1 = (char *)malloc(strlen(p) + 1);
					strcpy(nume1, p);
				}
				if (nr == 4) {
					if (tip == '1') {
						b1_8 = atoi(p);
					}
					if (tip == '2') {
						b1_16 = atoi(p);
					}
					if (tip == '3') {
						b1_32 = atoi(p);
					}
				}
				if (nr == 5) {
					if (tip == '1') {
						b2_8 = atoi(p);
					}
					if (tip == '2') {
						b2_32 = atoi(p);
					}
					if (tip == '3') {
						b2_32 = atoi(p);
					}
				}
				if (nr == 6) {
					nume2 = (char *)malloc(strlen(p) + 1);
					strcpy(nume2, p);
				}
				nr++;
				p = strtok(NULL, " ");
			}
			unsigned int c1 = 0, c2 = 0;
			if (tip == '1') {
				c1 = sizeof(int8_t);
				c2 = sizeof(int8_t);
			}
			if (tip == '2') {
				c1 = sizeof(int16_t);
				c2 = sizeof(int32_t);
			}
			if (tip == '3') {
				c1 = sizeof(int32_t);
				c2 = sizeof(int32_t);
			}
			struct data_structure *DS = malloc(sizeof(data_structure));
			DS->header = malloc(sizeof(head));
			DS->header->type = tip;
			DS->header->len = strlen(nume1) + strlen(nume2) + 2 + c1 + c2;
			DS->data = malloc(DS->header->len);
			memcpy(DS->data, nume1, strlen(nume1) + 1);
			if(tip == '1') {
				memcpy(DS->data + strlen(nume1) + 1, &b1_8, c1);
				memcpy(DS->data + strlen(nume1) + c1 + 1, &b2_8, c2);
				memcpy(DS->data + strlen(nume1) + c1 + 1 + c2, nume2, strlen(nume2) + 1);
			}
			if(tip == '2') {
				memcpy(DS->data + strlen(nume1) + 1, &b1_16, c1);
				memcpy(DS->data + strlen(nume1) + c1 + 1, &b2_32, c2);
				memcpy(DS->data + strlen(nume1) + c1 + 1 + c2, nume2, strlen(nume2) + 1);
			}
			if(tip == '3') {
				memcpy(DS->data + strlen(nume1) + 1, &b1_32, c1);
				memcpy(DS->data + strlen(nume1) + c1 + 1, &b2_32, c2);
				memcpy(DS->data + strlen(nume1) + c1 + 1 + c2, nume2, strlen(nume2) + 1);
			}
			add_at(&arr, &len, DS, (int)index);
			free(DS->header);
			free(DS->data);
			free(DS);
			free(nume1);
			free(nume2);
		}
		if (co == 2) {
			int nr = 0;
			char *nume1, *nume2, tip, *p;
			int8_t b1_8, b2_8;
			int16_t b1_16;
			int32_t b1_32, b2_32;
			p = strtok(comm, " ");
			while (p) {
				if (nr == 1) {
					tip = p[0];
				}
				if (nr == 2) {
					nume1 = (char *)malloc(strlen(p) + 1);
					strcpy(nume1, p);
				}
				if (nr == 3) {
					if (tip == '1') {
						b1_8 = atoi(p);
					}
					if (tip == '2') {
						b1_16 = atoi(p);
					}
					if (tip == '3') {
						b1_32 = atoi(p);
					}
				}
				if (nr == 4) {
					if (tip == '1') {
						b2_8 = atoi(p);
					}
					if (tip == '2') {
						b2_32 = atoi(p);
					}
					if (tip == '3') {
						b2_32 = atoi(p);
					}
				}
				if (nr == 5) {
					nume2 = (char *)malloc(strlen(p) + 1);
					strcpy(nume2, p);
				}
				nr++;
				p = strtok(NULL, " ");
			}
			unsigned int c1 = 0, c2 = 0;
			if (tip == '1') {
				c1 = sizeof(int8_t);
				c2 = sizeof(int8_t);
			}
			if (tip == '2') {
				c1 = sizeof(int16_t);
				c2 = sizeof(int32_t);
			}
			if (tip == '3') {
				c1 = sizeof(int32_t);
				c2 = sizeof(int32_t);
			}
			struct data_structure *DS = malloc(sizeof(data_structure));
			DS->header = malloc(sizeof(head));
			DS->header->type = tip;
			DS->header->len = strlen(nume1) + strlen(nume2) + 2 + c1 + c2;
			DS->data = malloc(DS->header->len);
			memcpy(DS->data, nume1, strlen(nume1) + 1);
			if(tip == '1') {
				memcpy(DS->data + strlen(nume1) + 1, &b1_8, c1);
				memcpy(DS->data + strlen(nume1) + c1 + 1, &b2_8, c2);
				memcpy(DS->data + strlen(nume1) + c1 + 1 + c2, nume2, strlen(nume2) + 1);
			}
			if(tip == '2') {
				memcpy(DS->data + strlen(nume1) + 1, &b1_16, c1);
				memcpy(DS->data + strlen(nume1) + c1 + 1, &b2_32, c2);
				memcpy(DS->data + strlen(nume1) + c1 + 1 + c2, nume2, strlen(nume2) + 1);
			}
			if(tip == '3') {
				memcpy(DS->data + strlen(nume1) + 1, &b1_32, c1);
				memcpy(DS->data + strlen(nume1) + c1 + 1, &b2_32, c2);
				memcpy(DS->data + strlen(nume1) + c1 + 1 + c2, nume2, strlen(nume2) + 1);
			}
			add_last(&arr, &len, DS);
			free(DS->header);
			free(DS->data);
			free(DS);
			free(nume1);
			free(nume2);
		}
		if (co == 3) {
			int ix = atoi(strstr(comm, " ") + 1);
			delete_at(&arr, &len, ix);
		}
		if (co == 4) {
			int indx = atoi(strstr(comm, " ") + 1);
			find(arr, len, indx);
		}
		if (co == 5) {
			print(arr, len);
		}
		if (co == 6) {
			ready = 1;
			//printf("%d\n", size_arr(arr, len));
			free(arr);
		}
	}
	return 0;
}
