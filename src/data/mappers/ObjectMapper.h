
#ifndef BEING_MAPPER_H_
#define BEING_MAPPER_H_

#include "Database.h"
#include "Being.h"
#include "rapidxml.h"

template <>
class Mapper<Being> {
	public:
		Mapper(Database &db);

		Being *xmlToModel(rapidxml::xml_node<> file);
		String modelToXml(Being *model);

	protected:

	private:
		Database _db;
};

template<>
Mapper<Being>::Mapper(Database &db) {_db = db;}

template<>
Being *Mapper<Being>::xmlToModel(rapidxml::xml_node<> file) {
	Being *model = _db.createBeing(file.first_node("vnum");		
	model->name = file.first_node("name");
	model->description = file.first_node("description");
	return model;
}

template<>
String modelToXml(Being *model) {
	String xml = "<being>\n";
	xml += "<vnum>" + model->vnum() + "</vnum>\n";
	xml += "<name>" + model->name + "</name>\n";
	xml += "<description>" + model->description + "</description>\n";
	xml += "</being>\n":
}

#endif /* BEING_MAPPER_H_ */
