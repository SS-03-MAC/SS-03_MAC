#include "bigint.h"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

BigInt *BigInt::mul(const BigInt *v) {
	BigInt *result = new BigInt(0x00, false);
	BigInt *tmp = new BigInt(0x00, false);
	BigInt *mul = new BigInt(this);
	BigInt *val = new BigInt(v);
	uint8_t i = 0;
	uint8_t lsb = 0;
	bool negative = (mul->negative != val->negative);
	mul->negative = false;
	val->negative = false;

	while (val->data->length != 0) {
		lsb = val->data->lsb();
		for (i = 0; i < 8; i++) {
			if ((lsb & 1) == 1) {
				delete result;
				result = tmp->add(mul);
				delete tmp;
				tmp = new BigInt(result);
			}
			lsb = lsb >> 1;
			mul->left_shift(1);
		}
		val->right_shift(8);
	}

	result->negative = negative;

	delete tmp;
	delete mul;
	delete val;

	return result;
}

BigInt *BigInt::div(const BigInt *v) {
	BigInt *result = new BigInt(0x00, false);
	BigInt *tmp = new BigInt(0x01, false);
	BigInt *num_tmp = new BigInt(0x00, false);
	BigInt *num = new BigInt(this);
	BigInt *den = new BigInt(v);
	uint64_t shift = 0;
	bool negative = (num->negative != den->negative);
	num->negative = false;
	den->negative = false;

	if (den->cmp(num_tmp) == 0) {
		delete tmp;
		delete num_tmp;
		delete num;
		delete den;
		return result;
	}

	if (den->cmp(tmp) == 0) {
		delete result;
		result = new BigInt(num);
		delete tmp;
		delete num_tmp;
		delete num;
		delete den;

		return result;
	}

	if (den->cmp(num) == 0) {
		delete result;
		result = new BigInt(0x01, false);
		delete tmp;
		delete num_tmp;
		delete num;
		delete den;

		return result;
	}

	while (num->cmp(den) != -1) {
		shift = 0;
		delete tmp;
		tmp = new BigInt(den);

		while (num->cmp(tmp) == 1) {
			tmp->left_shift(1);
			shift += 1;
		}

		if (num->cmp(tmp) == -1) {
			shift -= 1;
			tmp->right_shift(1);
		}

		delete num_tmp;
		num_tmp = num->sub(tmp);

		delete num;
		num = new BigInt(num_tmp);

		delete tmp;
		tmp = new BigInt(0x01, false);
		tmp->left_shift(shift);

		delete num_tmp;
		num_tmp = result->add(tmp);

		delete result;
		result = new BigInt(num_tmp);
	}

	result->negative = negative;

	delete tmp;
	delete num_tmp;
	delete num;
	delete den;

	return result;
}