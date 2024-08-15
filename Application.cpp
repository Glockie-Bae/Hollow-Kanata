#include"Util.h"
#include"Resources_Manager.h"

#include<thread>
#include<chrono>
#include<iostream>
#include<graphics.h>


static void draw_background() {
	static IMAGE* img_background = RescourcesManager::get_instance()->find_image("background");
	static Rect rect_dst = {
		(getwidth() - img_background->getwidth()) / 2,
		(getheight() - img_background->getheight()) / 2,
		img_background->getwidth(),
		img_background->getheight()
	};

	putimage_ex(img_background, &rect_dst);
}

int main(int argc, char** argv) {
	HWND hwnd = initgraph(1280, 720, EW_SHOWCONSOLE);
	SetWindowText(hwnd, _T("Hollow Katana"));
	
	try {
		RescourcesManager::load();
	}
	catch (const LPCTSTR id) {
		TCHAR err_msg[512];
		_stprintf_s(err_msg, _T("无法加载 : %s"), id);
		MessageBox(hwnd, err_msg, _T("资源加载失败"), MB_OK | MB_ICONERROR);
		return -1;
	}

	const std::chrono::nanoseconds frame_duration(100000000 / 144);
	std::chrono::steady_clock::time_point last_tick = std::chrono::steady_clock::now();

	ExMessage msg;
	bool is_quit = false;

	// 开始批量处理绘图
	BeginBatchDraw();

	while (!is_quit) {
		while (peekmessage(&msg)) {
			// 处理信息
		}

		std::chrono::steady_clock::time_point frame_start = std::chrono::steady_clock::now();
		std::chrono::duration<float> delta = std::chrono::duration<float>(frame_start - last_tick);

		// 处理更新

		setbkcolor(BLACK);
		// 清理上一帧画面
		cleardevice();

		// 处理绘图
		// 绘制背景
		draw_background();

		FlushBatchDraw();

		last_tick = frame_start;
		std::chrono::nanoseconds sleep_duration = frame_duration - (std::chrono::steady_clock::now() - frame_start);
		if (sleep_duration > std::chrono::nanoseconds(0)) {
			std::this_thread::sleep_for(sleep_duration);
		}
	}

	EndBatchDraw();

	return 0;
}