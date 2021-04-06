#pragma once
#include<vector>

class In
{
public:
	In() = default;
	~In() = default;
	void setSize();
	void initLights();
	int getLights() const;
	int getSize() const;
	bool getOk() const { return isOk; }
	void setOk() { isOk = false; };
	void clearLight() { m_lights = 0; };
private:
	int m_size ;
	int m_lights = 0;
	bool isOk = false;
};