#include "pch.h"
#include <iostream>
#include <vector>
#include "settings/packet.h"
#include "settings/packet_data.h"
#include <string>
#include <chrono>
#include <fstream>
#include <thread>
#include <windows.h>
#include <algorithm>
#include <array>
#pragma warning(disable:4996)
int PACKET_LIMIT = 255;
int main()
{
	create_data();
	std::array<FILE*, PACKET_MAX_NUM> fileGC {
		fopen("GC.txt", "w"),
		fopen("CG.txt", "w"),
		fopen("GG.txt", "w"),
		fopen("GD.txt", "w"),
		fopen("DG.txt", "w"),
		fopen("GP.txt", "w"),
		fopen("PG.txt", "w")
	};
	for (auto i : fileGC)
		if (!i) {
			MessageBox(nullptr, L"Error: Create File",nullptr, MB_OK | MB_ICONERROR);
			return 0;
		}
	for (int i = GC; i < fileGC.size(); i++) {
		std::sort(packet_data[i].begin(), packet_data[i].end());
		for (int j = packet_data[i].front(); j <= PACKET_LIMIT; j++)
			if (std::find(packet_data[i].begin(), packet_data[i].end(), j) == packet_data[i].end())
				fprintf(fileGC[i], "EMPTY: %d\n", j);
			else
				fprintf(fileGC[i], "USED: %d\n", j);
		fflush(fileGC[i]);
		fclose(fileGC[i]);
	}
	int wait = 0;
	std::cout << "Completed Successfully\n";
	while (wait > 0) {
		std::cout << "Close After: " << wait << " Second(s)" << std::endl;
		wait--;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	return 0;
}