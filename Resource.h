#pragma once
#include <string>

/*	TODO: resource management, then clean code and fix waves 
 *  (currently Enemies' sprites are losing its textures when Wave containing them is pushed to vector (copy constructors issue?)
 *		resources.txt:
 *	
 *	1	resources\cursor.png
 *	2	resources\menu\background.jpg
 *	3	resources\menu\title.png
 *	4	resources\menu\button_play.png
 *	5	resources\menu\button_options.png
 *	6	resources\menu\button_exit.png
 *	7	resources\enemies\enemy_properties.txt
 *	8	resources\enemies\hotdog.png
 *	9	resources\enemies\hotdog2.png
 *	10	resources\enemies\kaczucha.png
 *	11	resources\enemies\kaczucha2.png
 *	12	resources\enemies\kaczucha3.png
 *	13	resources\levels\level_1_data.txt
 *	14	resources\levels\level_1_track.png
 *	15	resources\levels\level_1.png
 */

class Resource
{
private:
	int m_ID;
public:
	Resource() : m_ID(0) {}
	virtual ~Resource();
	virtual bool loadFromFile() = 0;
};

