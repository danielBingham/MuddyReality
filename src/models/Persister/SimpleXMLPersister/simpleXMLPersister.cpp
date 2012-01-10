/***********************************************************************************
 * File: simpleXMLPersister.cpp
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

#include "SimpleXMLPersister.h"

/********************************************************************************
 * START Mapper
 ********************************************************************************/
Mapper::Mapper(Config *config, String name) {
	_name = name;
	_config = config;
}
Mapper::~Mapper() {}

String Mapper::getName() {return _name;}
Config *Mapper::getConfig() {return _config;}

String Mapper::getOpeningTag() {return "<"+getName()+">";}
String Mapper::getClosingTag() {return "</"+getName()+">";}

void Mapper::getModelString(ifstream file) {
	String xml = "";
	String line = "";
	while(file.good() && line.find(getClosingTag()) != String::npos) {
		getline(file, line);
		xml += line;
	}
}

/********************************************************************************
 * END Mapper / START SimpleXMLPersister
 ********************************************************************************/
SimpleXMLPersister::SimpleXMLPersister() {_mapper = 0;}
SimpleXMLPersister::SimpleXMLPersister(Mapper *mapper) {_mapper = mapper;}
SimpleXMLPersister::~SimpleXMLPersister() {
	if(_mapper != 0) {
		delete _mapper;
	}
}

void SimpleXMLPersister::save(Store *store) {
	ostream file(getMapper()->getFileName());
	for(int i = 0; i < store->size(); i++) {
		fprintf("%s\n", getMapper()->modelToXML(store[i]));
	}
	file.close();
}

void SimpleXMLPersister::load(Store *store) {
	istream file(getMapper()->getFileName());
	while(file.good()) {
		store->add(getMapper()->xmlToModel(getMapper()->getModelString(file)));
	}
	file.close();
}

/********************************************************************************
 * END SimpleXMLPersister
 ********************************************************************************/
