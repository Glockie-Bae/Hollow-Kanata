#pragma once
#include"Util.h"
#include"Timer.h"
#include"Atlas.h"
#include"Vector2D.h"

#include<vector>
#include<functional>

class Animation {
public:
	enum class AnchorMode {
		// ÃªµãÄ£Ê½
		// ¾ÓÖÐÃªµã µ×²¿¾ÓÖÐÃªµã
		Centered,
		BottomCentered
	};

public:
	Animation() {
		timer.set_one_shot(false);
		timer.set_on_timeout(
			[&]()
			{
				idx_frame++;
				if (idx_frame >= frame_list.size()) {
					idx_frame = is_loop ? 0 : frame_list.size() - 1;
					if (!is_loop && on_finished)
						on_finished();
				}
			}
		);
	}

	~Animation() {}

	void reset() {
		timer.restart();
		idx_frame = 0;
	}

	void set_anchor_mode(AnchorMode mode) {
		anchor_mode = mode;
	}

	void set_position(const Vector2D& pos) {
		position = pos;
	}

	void set_loop(bool flag) {
		is_loop = flag;
	}

	void set_interval(float interval) {
		timer.set_wait_time(interval);
	}

	void set_on_finished(std::function<void()> func) {
		on_finished = func;
	}

	void on_update(float delta) {
		timer.on_update(delta);
	}

	void on_render() {
		const Frame& frame = frame_list[idx_frame];

		Rect rect_dst;
		rect_dst.x = (int)position.x - frame.rect_src.x / 2;
		rect_dst.y = (anchor_mode == AnchorMode::Centered) ? (int)position.y - frame.rect_src.h / 2 : (int)position.y - frame.rect_src.h;
		rect_dst.w = frame.rect_src.w;
		rect_dst.h = frame.rect_src.h;

		// rect_dst £ºäÖÈ¾Í¼Æ¬Î»ÖÃ  rect_src £ºäÖÈ¾Í¼Æ¬´óÐ¡
		putimage_ex(frame.img, &rect_dst, &frame.rect_src);
	}

private:
	// Ö¡Í¼Ïñ
	struct Frame
	{
		Rect rect_src;
		IMAGE* img = NULL;

		Frame() {}
		~Frame() {}

		Frame(IMAGE* img, const Rect& rect_src)
			: img(img), rect_src(rect_src) {}
	};

public:
	// ³¤ÌõÍ¼Æ¬Ìí¼Ó¶¯»­Ö¡
	void add_frame(IMAGE* img, int num_h) {
		int width = img->getwidth();
		int height = img->getheight();
		int width_frame = width / num_h;

		for (int i = 0; i < width_frame; i++) {
			Rect rect_src;
			rect_src.x = i * width_frame;
			rect_src.w = width_frame;
			rect_src.y = 0;
			rect_src.h = height;

			frame_list.emplace_back(img, rect_src);
		}
	}

	// Í¼Æ¬¼¯Ìí¼Ó¶¯»­Ö¡
	void add_frame(Atlas* atlas) {
		for (int i = 0; i < atlas->get_size(); i++) {
			IMAGE* img = atlas->get_img(i);

			Rect rect_src;
			rect_src.x = 0;
			rect_src.y = 0;
			rect_src.w = img->getwidth();
			rect_src.h = img->getheight();

			frame_list.emplace_back(img, rect_src);
		}
	}

private:
	Timer timer;
	Vector2D position;
	bool is_loop = true;
	size_t idx_frame = 0;
	std::vector<Frame> frame_list;
	std::function<void()> on_finished;
	AnchorMode anchor_mode = AnchorMode::Centered;
};