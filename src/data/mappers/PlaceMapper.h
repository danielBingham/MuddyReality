
#ifndef PLACE_MAPPER_H_
#define PLACE_MAPPER_H_

#include "Database.h"
#include "Place.h"
#include "rapidxml.h"

template <>
class Mapper<Place> {
	public:
		Mapper();

		//TODO Redefine getVnum(), template specializations are a redefinition of the original template.
		void xmlToModel(Place *model, rapidxml::xml_node<> file);
		String modelToXml(Place *model);

	protected:

	private:
};

template<>
Mapper<Place>::Mapper() {}

template<>
Place *Mapper<Place>::xmlToModel(Place *model, rapidxml::xml_node<> file) {
	model->vnum(vnum);
	model->name = file.first_node("name")->value();
	model->description = file.first_node("description")->value();

	return model;
}

template<>
String modelToXml(Place *model) {
	String xml = "<place>\n";
	xml += "<vnum>" + model->vnum() + "</vnum>\n";
	xml += "<name>" + model->name + "</name>\n";
	xml += "<description>" + model->description + "</description>\n";
	xml += "</place>\n":
	return xml;
}

#endif /* PLACE_MAPPER_H_ */
