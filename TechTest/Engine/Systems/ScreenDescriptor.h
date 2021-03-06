#pragma once
#include <Engine/Serialization/ISerializable.h>
#include <Engine/Core/StringUtils.h>
#include <Engine/EntityComponent/RenderLayer.h>


struct SObjectDescriptor : public CSerializableObject
{
	enum class EType : char
	{
		Texture,
		Button,
		Text
	};

	void OnLoad(pugi::xml_node& node) override
	{
		SERIALIZE(node, "id", _id);
		SERIALIZE_ENUM(node, "renderLayer", _renderLayer);
		SERIALIZE_ENUM(node, "type", _type);
		SERIALIZE(node, "texture", _texture);
		SERIALIZE(node, "x", _x);
		SERIALIZE(node, "y", _y);
		SERIALIZE(node, "z", _z);
		SERIALIZE(node, "width", _width);
		SERIALIZE(node, "height", _height);
		SERIALIZE(node, "alpha", _alpha);
		SERIALIZE(node, "text", _text);

		StringUtils::Replace(_text, "<newline>", "\n");
	}

	RenderLayer::ERenderLayer _renderLayer = RenderLayer::ERenderLayer::World;
	EType _type = EType::Texture;
	std::string _id;
	std::string _texture;
	float _x = 0.0f;
	float _y = 0.0f;
	float _z = 0.0f;
	float _width = 0.0f;
	float _height = 0.0f;
	float _alpha = 1.0f;
	std::string _text;
};

struct SScreenDescriptor : public CSerializableObject
{
	void OnLoad(pugi::xml_node& node) override
	{
		SERIALIZE(node, "objects", _objects);
	}

	std::vector<SObjectDescriptor> _objects;
};