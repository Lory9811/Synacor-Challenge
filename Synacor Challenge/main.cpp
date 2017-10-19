#include "System.h"

int main(int argc, char** argv) {
	System::Start();
	while (System::get_status() != System::STOPPED) {
		System::Update();
	}
}