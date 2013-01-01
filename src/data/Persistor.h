/***********************************************************************************
 * File: Persistor.h
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

#ifndef PERSISTOR_H_
#define PERSISTOR_H_

#include "Store.h"
#include "Mapper.h"
#include <iostream>


template <class Model>
class Persistor {
	public:
		Persistor(Store<Model> &store, Mapper<Model> &mapper);
		~Persistor();
	
		void save(String filename, String root);
		void save(String filename, String root, id_num minVnum, id_num maxVnum);

		void load(String filename);

	protected:

	private:
		Store<Model> _store;
		Mapper<Model> _mapper;
};

/********************************************************************************
 * START Persistor
 ********************************************************************************/

template <class Model>
Persistor::Persistor(Store<Model> &store, Mapper<Model> &mapper) {
	_store = store;
	_mapper = mapper;
}
template <class Model>
Persistor<Model>::~Persistor() {}

template <class Model>
void Persistor<Model>::save(String filename, String root, id_num minVnum, id_num maxVnum) {
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
void Persistor<Model>::save(String filename, String root) {
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
void Persistor<Model>::load(String filename) {
	
	istream file(filename);
	String buf, fileContents;
	while(file.good()) {
		getline(file, buf);
		fileContents += buf;	
	}
	
	rapidxml::xml_document<> parseFile;
	parsedFile.parse(fileContents.c_str());
	for(xml_node<> modelNode = parsedFile.first_node(); modelNode; modelNode = modelNode.next_sibling()) {
		mapper.xmlToModel(_store.create(mapper.getVnum(modelNode), modelNode);
	}
	file.close();
}

/********************************************************************************
 * END Persistor
 ********************************************************************************/
#endif /* PERSISTOR_H_ */
