#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

class Environment
{
public:
	Environment (int light, int water, int temperature);
	int light() { return m_light; };
	int water() { return m_water; };
	int temperature() { return m_temperature; };
	void changeLight(int delta) { m_light += delta; };
	void changeWater(int delta) { m_water += delta; };
	void changeTemperature(int delta) { m_temperature += delta; };
	
private:
	int m_light;
	int m_water;
	int m_temperature;
};

#endif
