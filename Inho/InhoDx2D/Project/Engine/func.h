#pragma once

template<typename T, UINT SIZE>
void Delete_Array(T* (&Arr)[SIZE]) {
	for (int i = 0; i < SIZE; i++) {
		if (nullptr != Arr[i]) {
			delete Arr[i];
			Arr[i] = nullptr;
		}
	}
}