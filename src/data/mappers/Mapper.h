
#ifndef MAPPER_H_
#define MAPPER_H_



template <class Model>
class Mapper {
	public:
		void getVnum(rapidxml::xml_node<> file);
		virtual void xmlToModel(Model *model, rapidxml::xml_node<> file) = 0;
		virtual String modelToXML(Model *model) = 0;

	protected:

	private:
};

template <class Model>
void Mapper<Model>::getVnum(rapidxml::xml_node<> file) {
	id_num vnum = -1;
	sscanf(file.first_node("vnum")->value(), "%lu", vnum); 
	return vnum;
}


#endif /* MAPPER_H_ */
