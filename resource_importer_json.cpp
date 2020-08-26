/*************************************************************************/
/*  resource_importer_json.cpp                                           */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2020 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2020 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "resource_importer_json.h"
#include "core/io/file_access_pack.h"

String ResourceImporterJSON::get_preset_name(int p_idx) const {
	return String();
}

void ResourceImporterJSON::get_import_options(List<ImportOption> *r_options, int p_preset) const {
}

bool ResourceImporterJSON::get_option_visibility(const String &p_option, const Map<StringName, Variant> &p_options) const {
	return true;
}

String ResourceImporterJSON::get_importer_name() const {
	return "JSON";
}

String ResourceImporterJSON::get_visible_name() const {
	return "JSON";
}

void ResourceImporterJSON::get_recognized_extensions(List<String> *p_extensions) const {
	p_extensions->push_back("json");
}

String ResourceImporterJSON::get_save_extension() const {
	return "res";
}

String ResourceImporterJSON::get_resource_type() const {
	return "JSONData";
}

int ResourceImporterJSON::get_preset_count() const {
	return 0;
}

Error ResourceImporterJSON::import(const String &p_source_file, const String &p_save_path, const Map<StringName, Variant> &p_options, List<String> *r_platform_variants, List<String> *r_gen_files, Variant *r_metadata) {

	FileAccess *file = FileAccess::create(FileAccess::ACCESS_RESOURCES);
	Error err;
	String json_string = file->get_file_as_string(p_source_file, &err);
	ERR_FAIL_COND_V_MSG(err != OK, FAILED, "Can not open json file.");
	Ref<JSONData> json_data;
	json_data.instance();
	String error_string;
	int error_line;
	Variant data;
	err = JSON::parse(json_string, data, error_string, error_line);
	ERR_FAIL_COND_V_MSG(err != OK, FAILED, String("Can not parse JSON ") + error_string + " on line " + rtos(error_line) + ".");
	json_data->set_data(data);
	return ResourceSaver::save(p_save_path + ".res", json_data);
}
