#include "ParticlePGenerator.h"


std::default_random_engine ParticlePGenerator::gen(std::random_device{}());

ParticlePGenerator::ParticlePGenerator(int n, Vector3D pRange, Vector3D IniPos, Vector3D dRange, Vector3D IniDir, float initime, float timerange, float ypendiente, stats ParticulaB, PxScene* GScene)
{
	nParticles = 0;
	maxParticles = n;
	posRange = pRange;
	iniPos = IniPos;
	dirRange = dRange;
	iniDir = IniDir;
	iniTime = initime;
	timeRange = timerange;
	yPendiente = ypendiente;
	dist = std::normal_distribution<float>(0, 1);
	particulaB = ParticulaB;
	gScene = GScene;
}

ParticlePGenerator::~ParticlePGenerator()
{
}

void ParticlePGenerator::update(double t)
{
	if (nParticles < maxParticles)
	{

		for (nParticles = nParticles; nParticles < maxParticles; nParticles++)
		{
			createParticle();
		}
	}

	for (int i = 0; i < particles.size(); i++)
	{
		if (particles[i]->canDestroy(t))
		{
			particles.erase(particles.begin() + i);
			nParticles--;

		}
		else
		{
			i++;
		}
	}
	integrate(t);
}


void ParticlePGenerator::createParticle()
{
	//mirar los rangos de posicion y pillar un random entre la inipos-posRange/2 y 
	//inipos +posRange/2+1
	Vector3D pos;
	pos = generateRandom(iniPos, posRange);
	Vector3D dir;
	dir = generateRandom(iniDir, dirRange);
	float lifetime;
	lifetime = iniTime + dist(gen) * timeRange;
	Vector3D accel = { 0,0,0 };
	particles.push_back(std::make_unique<Particle>(pos, dir,gScene,particulaB.mass, lifetime,particulaB.size,particulaB.color));
}

Vector3D ParticlePGenerator::generateRandom(Vector3D ini, Vector3D range)
{
	//tiene que hacerse por floats en vez de por vector
	Vector3D sol;

	sol.x = dist(gen) * range.x + ini.x;
	if (yPendiente != 0) { sol.y = sol.x * yPendiente + ini.y; }
	else {
		sol.y = dist(gen) * range.y + ini.y;
	}
	sol.z = dist(gen) * range.z + ini.z;
	return sol;
}
