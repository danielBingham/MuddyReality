
#ifndef BEING_MAPPER_H_
#define BEING_MAPPER_H_

#include "Database.h"
#include "Being.h"
#include "rapidxml.h"

template <>
class Mapper<Being> {
	public:
		Mapper();

		void xmlToModel(Being *model, rapidxml::xml_node<> file);
		String modelToXml(Being *model);

	protected:

	private:
};

template <>
Mapper<Being>::Mapper() {}

template<>
void Mapper<Being>::xmlToModel(Being *model, rapidxml::xml_node<> file) {

	model->name = file.first_node("name")->value();
	model->description = file.first_node("description")->value();

	return model;
}

template<>
String modelToXml(Being *model) {
	String xml = "<being>\n";
	xml += "<vnum>" + model->vnum() + "</vnum>\n";
	xml += "<name>" + model->name + "</name>\n";
	xml += "<description>" + model->description + "</description>\n";
	xml += "</being>\n":
	return xml;
}

#endif /* BEING_MAPPER_H_ */
