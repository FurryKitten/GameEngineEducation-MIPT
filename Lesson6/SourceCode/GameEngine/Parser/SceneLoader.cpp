#include "SceneLoader.h"
#include <vector>
#include "../EntitySystem/ecsPhys.h"
#include "../EntitySystem/ecsScripts.h"
#include "../EntitySystem/ecsMesh.h"

SceneLoader::SceneLoader(flecs::world& ecs, std::string filename) : ecs(ecs)
{
	doc.LoadFile(filename.c_str());
}

void SceneLoader::registerEntities()
{
	auto entitiesXml = doc.FirstChildElement("entities");
	auto entityXml = entitiesXml->FirstChildElement("entity");
	while (entityXml != NULL)
	{
		std::vector<tinyxml2::XMLElement*> elements;
		auto transformEl = entityXml->FirstChildElement("transform");
		elements.push_back(transformEl->FirstChildElement("position"));

		auto physicsEl = entityXml->FirstChildElement("physics");
		elements.push_back(physicsEl->FirstChildElement("friction"));
		elements.push_back(physicsEl->FirstChildElement("bounciness"));
		elements.push_back(physicsEl->FirstChildElement("gravity"));
		elements.push_back(physicsEl->FirstChildElement("velocity"));
		elements.push_back(physicsEl->FirstChildElement("bouncePlane"));

		elements.push_back(entityXml->FirstChildElement("scripts"));
		elements.push_back(entityXml->FirstChildElement("mesh"));

		auto newEntity = ecs.entity();
		for (const auto& el : elements)
		{
			if (el == NULL) continue;
			setComponent(el, newEntity);
		}

		entityXml = entityXml->NextSiblingElement("entity");
	}
}

void SceneLoader::setComponent(tinyxml2::XMLElement* el, flecs::entity& entity)
{
	std::string compType = el->Name();
	switch (types.at(compType))
	{
	case POSITION:
		entity.set(Position{
			el->FirstChildElement("x")->FloatText(),
			el->FirstChildElement("y")->FloatText(),
			el->FirstChildElement("z")->FloatText()
		});
		break;
	case VELOCITY:
		entity.set(Velocity{
			el->FirstChildElement("x")->FloatText(),
			el->FirstChildElement("y")->FloatText(),
			el->FirstChildElement("z")->FloatText()
		});
		break;
	case FRICTION:
		entity.set(FrictionAmount{
			el->FloatText(),
		});
		break;
	case BOUNCINESS:
		entity.set(Bounciness{
			el->FloatText(),
		});
		break;
	case BOUNCE_PLANE:
		entity.set(BouncePlane{
			el->FirstChildElement("x")->FloatText(),
			el->FirstChildElement("y")->FloatText(),
			el->FirstChildElement("z")->FloatText(),
			el->FirstChildElement("w")->FloatText()
		});
		break;
	case GRAVITY:
		entity.set(Gravity{
			el->FirstChildElement("x")->FloatText(),
			el->FirstChildElement("y")->FloatText(),
			el->FirstChildElement("z")->FloatText()
		});
		break;
	case SCRIPTS:
	{
		std::vector<std::string> scripts;
		auto scriptXml = el->FirstChildElement("script");
		while (scriptXml != NULL)
		{
			scripts.push_back(scriptXml->Attribute("filename"));
			scriptXml = scriptXml->NextSiblingElement("script");
		}
		entity.set(ScriptCreate{ scripts });
		break;
	}
	case MESH:
		if (strcmp(el->Attribute("type"), "cubeMesh") != 0)
			return;
		entity.add<CubeMesh>();
		break;
	}
}
