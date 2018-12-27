#pragma once

#include <libs\pugixml\pugixml.hpp>

#include <vector>

class ISerializable
{
public:
	virtual void Load(const std::string& fileName) = 0;
	virtual void LoadXmlNode(pugi::xml_node& node) = 0;
	virtual void OnLoad(pugi::xml_node& node) = 0;
};

class CSerializableObject : public ISerializable
{
public:
	void Load(const std::string& fileName) override;
	void LoadXmlNode(pugi::xml_node& node) override;

private:
	pugi::xml_node _rootNode;
};


template<class T>
struct SSerializatorEnum
{
	static void Serialize(pugi::xml_node& node, const char* key, T& member)
	{
		member = static_cast<T>(node.attribute(key).as_int(static_cast<int>(member)));
	}
};

template<class T>
struct SSerializatorTraits
{
	static void Serialize(pugi::xml_node& node, const char* key, T& member) 
	{
		pugi::xml_node childNode = node.child(key);
		member.LoadXmlNode(node);
	}
};

template<class T>
struct SSerializatorTraits<std::vector<T>>
{
	static void Serialize(pugi::xml_node& node, const char* key, std::vector<T>& member)
	{
		pugi::xml_node groupNode = node.child(key);

		for (pugi::xml_node_iterator it = groupNode.begin(); it != groupNode.end(); ++it)
		{
			member.emplace_back();
			T& newValue = member.back();
			pugi::xml_node childNode = *it;
			newValue.LoadXmlNode(childNode);
		}
	}
};

template<>
struct SSerializatorTraits<int>
{
	static void Serialize(pugi::xml_node& node, const char* key, int& member)
	{
		member = node.attribute(key).as_int(member);
	}
};

template<>
struct SSerializatorTraits<bool>
{
	static void Serialize(pugi::xml_node& node, const char* key, bool& member)
	{
		member = node.attribute(key).as_bool(member);
	}
};

template<>
struct SSerializatorTraits<float>
{
	static void Serialize(pugi::xml_node& node, const char* key, float& member)
	{
		member = node.attribute(key).as_float(member);
	}
};

template<>
struct SSerializatorTraits<double>
{
	static void Serialize(pugi::xml_node& node, const char* key, double& member)
	{
		member = node.attribute(key).as_double(member);
	}
};

template<>
struct SSerializatorTraits<long long>
{
	static void Serialize(pugi::xml_node& node, const char* key, long long& member)
	{
		member = node.attribute(key).as_llong(member);
	}
};

template<>
struct SSerializatorTraits<std::string>
{
	static void Serialize(pugi::xml_node& node, const char* key, std::string& member)
	{
		member = node.attribute(key).as_string(member.c_str());
	}
};

#define SERIALIZE(XmlNode, KeyId, Member) \
	SSerializatorTraits<decltype(Member)>::Serialize(XmlNode, KeyId, Member);

#define SERIALIZE_ENUM(XmlNode, KeyId, Member) \
	SSerializatorEnum<decltype(Member)>::Serialize(XmlNode, KeyId, Member);