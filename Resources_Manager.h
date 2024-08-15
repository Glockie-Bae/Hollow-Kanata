#pragma once
#include"Atlas.h"
#include"Util.h"

#include<string>
#include<graphics.h>
#include<unordered_map>

class RescourcesManager {

public:
	static RescourcesManager* get_instance();

	static void load() { get_instance()->Iload(); }

	IMAGE* find_image(const std::string& file) const;
	Atlas* find_atlas(const std::string& file) const;

private:
	void Iload();

	static RescourcesManager* manager;

	std::unordered_map<std::string, Atlas*> atlas_pool;
	std::unordered_map<std::string, IMAGE*> image_pool;
private:
	RescourcesManager();
	~RescourcesManager();

	// Í¼Æ¬·´×ª
	void flip_image(IMAGE* src_image, IMAGE* dst_image, int num_h = 1);
	void flip_image(const std::string& src_id, const std::string dst_id, int num_h = 1);
	void flip_atlas(const std::string& src_id, const std::string dst_id);
};