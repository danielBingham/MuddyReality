/***********************************************************************************
 * File: SimpleXMLPersister.h
 * Definition:
 *
 * Contents:
 *  
 *
 * Copyright:
 *		Copyright (C) 2009-2011 Daniel Bingham (http://www.theroadgoeson.com)
 *
 * License:
 *
 * This software is licensed under the MIT Open Source License which reads as
 * follows:
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in the
 * Software without restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information see here: http://www.opensource.org/licenses/mit-license.php
 ***********************************************************************************/

#ifndef SIMPLEXMLPERSISTER_H_
#define SIMPLEXMLPERSISTER_H_

#include "Store.h"
#include <iostream>

template <class Model>
class Mapper {
	public:
		Mapper(Config *config);
		~Mapper();

		virtual Model *xmlToModel(rapidxml::xml_node<> file) = 0;
		virtual String modelToXML(Model *model) = 0;

	protected:
		Config *getConfig();

	private:
		Config *_config;
};

template <class Model>
class SimpleXMLPersister: public Persister {
	public:
		SimpleXMLPersister(Store<Model> *store, Mapper<Model> &mapper);
		~SimpleXMLPersister();
	
		void save(String filename, String root);
		void save(String filename, String root, id_num minVnum, id_num maxVnum);

		void load(String filename);

	protected:

	private:
		Store<Model> *_store;
		Mapper<Model> _mapper;

		String _fileContents;
		rapidxml::xml_document<> _parsedFile;

};

/********************************************************************************
 * START Mapper
 ********************************************************************************/
template <class Model>
Mapper<Model>::Mapper(Config *config) {
	_config = config;
}

template <class Model>
Mapper<Model>::~Mapper() {}

template <class Model>
Config *Mapper<Model>::getConfig() {return _config;}

/********************************************************************************
 * END Mapper / START SimpleXMLPersister
 ********************************************************************************/

template <class Model>
SimpleXMLPersister::SimpleXMLPersister(Store<Model> *store, Mapper<Model> &mapper) {
	_store = store;
	_mapper = mapper;
}
template <class Model>
SimpleXMLPersister<Model>::~SimpleXMLPersister() {}

template <class Model>
void SimpleXMLPersister<Model>::save(String filename, String root, id_num minVnum, id_num maxVnum) {
	ostream file(filename);
	file << "<" << root << " min=\"" << minVnum << "\" max=\"" << maxVnum << "\">\n"; 

	StoreIterator it(_store);
	for(Model *toSave = it.begin(minVnum, maxVnum); toSave != NULL; toSave = it.next()) {
		 file << _mapper.modelToXML(toSave);
	}
	file << "</" << root << ">\n";
	file.close();
}

template <class Model>
void SimpleXMLPersistor<Model>::save(String filename, String root) {
	ostream file(filename);
	file << "<" << root << " min=\"" << minVnum << "\" max=\"" << maxVnum << "\">\n"; 

	StoreIterator it(_store);
	for(Model *toSave = it.begin(minVnum, maxVnum); toSave != NULL; toSave = it.next()) {
		 file << _mapper.modelToXML(toSave);
	}
	file << "</" << root << ">\n";
	file.close();

template <class Model>
void SimpleXMLPersister<Model>::load(String filename) {
	istream file(filename);
	String buf;
	while(file.good()) {
		getline(file, buf);
		_fileContents += buf;	
	}
	_parsedFile.parse(_fileContents.c_str());

	for(xml_node<> modelNode = _parsedFile.first_node(); modelNode; modelNode = modelNode.next_sibling()) {
		_store->add(mapper.xmlToModel(modelNode);
	}
	file.close();
}

/********************************************************************************
 * END SimpleXMLPersister
 ********************************************************************************/
#endif /* SIMPLEXMLPERSISTER_H_ */
