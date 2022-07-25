/*************************************************************************/
/*  resource_importer_json.h  	                                         */
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
#ifndef RESOURCE_IMPORTER_JSON
#define RESOURCE_IMPORTER_JSON

#include "core/io/json.h"
#include "core/io/resource_importer.h"
#include "core/io/resource_saver.h"

class JSONData : public Resource {
	GDCLASS(JSONData, Resource);
	Dictionary data;

protected:
	static void _bind_methods() {

		ClassDB::bind_method(D_METHOD("set_data", "data"), &JSONData::set_data);
		ClassDB::bind_method(D_METHOD("get_data"), &JSONData::get_data);
		ClassDB::bind_method(D_METHOD("set_json", "json"), &JSONData::set_json);
		ClassDB::bind_method(D_METHOD("get_json"), &JSONData::get_json);

		ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "data"), "set_data", "get_data");
	}

public:
	Variant get_data() const {
		return data;
	}
	void set_data(Variant p_data) {
		data = p_data;
	}
	String get_json() const {
		Ref<JSON> json = memnew(JSON);
		return json->stringify(get_data());
	}
	void set_json(const String p_string) {
		Ref<JSON> json = memnew(JSON);
		int err = json->parse(p_string);
		ERR_FAIL_COND_MSG(err != OK, "Can not parse JSON: " + json->get_error_message() + " on line " + rtos( json->get_error_line()));
		set_data(json->get_data());
	}
	JSONData() {}
	~JSONData() {}
};

class ResourceImporterJSON : public ResourceImporter {
	GDCLASS(ResourceImporterJSON, ResourceImporter);

public:
	virtual String get_importer_name() const override;
	virtual String get_visible_name() const override;
	virtual void get_recognized_extensions(List<String> *p_extensions) const override;
	virtual String get_save_extension() const override;
	virtual String get_resource_type() const override;

	virtual int get_preset_count() const override;
	virtual String get_preset_name(int p_idx) const override;

	virtual void get_import_options(const String &p_path, List<ImportOption> *r_options, int p_preset = 0) const override;
	virtual bool
	get_option_visibility(const String &p_path, const String &p_option, const HashMap<StringName, Variant> &p_options) const override;
	virtual Error import(const String &p_source_file, const String &p_save_path,
			const HashMap<StringName, Variant> &p_options,
			List<String> *r_platform_variants,
			List<String> *r_gen_files = NULL,
			Variant *r_metadata = NULL) override;

	ResourceImporterJSON() {}
	~ResourceImporterJSON() {}
};
#endif // RESOURCE_IMPORTER_LOTTIE
