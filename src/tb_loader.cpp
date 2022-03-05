#include <tb_loader.h>

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <builders/csg_builder.h>
#include <builders/mesh_builder.h>

void TBLoader::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_map", "path"), &TBLoader::set_map);
	ClassDB::bind_method(D_METHOD("get_map"), &TBLoader::get_map);
	ClassDB::bind_method(D_METHOD("set_inverse_scale", "inverse_scale"), &TBLoader::set_inverse_scale);
	ClassDB::bind_method(D_METHOD("get_inverse_scale"), &TBLoader::get_inverse_scale);

	ClassDB::bind_method(D_METHOD("set_collision", "collision"), &TBLoader::set_collision);
	ClassDB::bind_method(D_METHOD("get_collision"), &TBLoader::get_collision);
	ClassDB::bind_method(D_METHOD("set_skip_hidden_layers", "skip_hidden_layers"), &TBLoader::set_skip_hidden_layers);
	ClassDB::bind_method(D_METHOD("get_skip_hidden_layers"), &TBLoader::get_skip_hidden_layers);

	ClassDB::bind_method(D_METHOD("set_entity_common", "entity_common"), &TBLoader::set_entity_common);
	ClassDB::bind_method(D_METHOD("get_entity_common"), &TBLoader::get_entity_common);

	ClassDB::bind_method(D_METHOD("clear"), &TBLoader::clear);
	ClassDB::bind_method(D_METHOD("build_meshes"), &TBLoader::build_meshes);
	ClassDB::bind_method(D_METHOD("build_combined_csg"), &TBLoader::build_combined_csg);

	ADD_GROUP("Map", "map_");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "map_resource", PROPERTY_HINT_FILE, "*.map"), "set_map", "get_map");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "map_inverse_scale", PROPERTY_HINT_NONE, "Inverse Scale"), "set_inverse_scale", "get_inverse_scale");

	ADD_GROUP("Options", "option_");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "option_collision", PROPERTY_HINT_NONE, "Collision"), "set_collision", "get_collision");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "option_skip_hidden_layers", PROPERTY_HINT_NONE, "Skip hidden layers"), "set_skip_hidden_layers", "get_skip_hidden_layers");

	ADD_GROUP("Entities", "entity_");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "entity_common", PROPERTY_HINT_NONE, "Common Entities"), "set_entity_common", "get_entity_common");
}

TBLoader::TBLoader()
{
}

TBLoader::~TBLoader()
{
}

void TBLoader::set_map(const String& map)
{
	m_map_path = map;
}

String TBLoader::get_map() const
{
	return m_map_path;
}

void TBLoader::set_inverse_scale(int scale)
{
	m_inverse_scale = scale;
}

int TBLoader::get_inverse_scale()
{
	return m_inverse_scale;
}

void TBLoader::set_collision(bool enabled)
{
	m_collision = enabled;
}

bool TBLoader::get_collision()
{
	return m_collision;
}

void TBLoader::set_skip_hidden_layers(bool enabled)
{
	m_skip_hidden_layers = enabled;
}

bool TBLoader::get_skip_hidden_layers()
{
	return m_skip_hidden_layers;
}

void TBLoader::set_entity_common(bool enabled)
{
	m_entity_common = enabled;
}

bool TBLoader::get_entity_common()
{
	return m_entity_common;
}

void TBLoader::clear()
{
	while (get_child_count() > 0) {
		auto child = get_child(0);
		remove_child(child);
		child->queue_free();
	}
}

void TBLoader::build_meshes()
{
	clear();

	MeshBuilder builder(this);
	builder.load_map(m_map_path);
	builder.build_map();
}

void TBLoader::build_combined_csg()
{
	clear();

	CSGBuilder builder(this);
	builder.load_map(m_map_path);
	builder.build_map();
}
