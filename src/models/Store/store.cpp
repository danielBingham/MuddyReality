/***********************************************************************************
 * File: store.cpp
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

#include "Store.h"

/********************************************************************************
 * START Store
 ********************************************************************************/

Store::Store() {
	_models = 0;
	_numberOfModels = 0;
	_topVirtualNumber = 0;
}
Store::~Store() {
	for(id_num i = 0; i < _numberOfModels; i++)
		delete _models[i];
	delete [] _models;
	_numberOfModels = 0;
}

Model *Store::operator[](id_num rnum) {
	if(0 <= rnum && rnum <= size())
		return _models[rnum];
	else
		throw ModelNotFoundException();
}
id_num Store::size() {
	return _numberOfModels;
}

Model *Store::get(id_num vnum) {
	id_num rnum = 0;
	try {
		rnum = real(vnum);
	} catch(ModelNotFoundException) {
		throw ModelNotFoundException();
	}
	return _models[rnum];

}
void Store::add(Model *model) {
	Model **tmp = new Model *[size()];

	for (id_num i = 0; i < size(); i++)
		tmp[i] = _models[i];


	delete[] _models;

	_numberOfModels++;
	_models = new Model *[size()];

	_models[size() - 1] = model;

	for (id_num i = 0; i < size() - 1; i++)
		_models[i] = tmp[i];

	delete[] tmp;

	order();

	if(model->vnum() > _topVirtualNumber) {
		_topVirtualNumber = model->vnum();
	}

}

void Store::remove(id_num vnum) {
	bool foundIt = false;

	Model **tmp = new Model *[_numberOfModels - 1];

	for (id_num i = 0; i < _numberOfModels - 1; i++) {
		if (_models[i]->vnum() < vnum)
			tmp[i] = _models[i];
		else if(_models[i]->vnum() == vnum) {
			foundIt = true;
			Model *toDelete = _models[i];
			delete toDelete;
		}
		else if(foundIt) {
			tmp[i] = _models[i + 1];
		} else {
			delete [] tmp;
			throw ModelNotFoundException();
		}
	}

	delete[] _models;

	_numberOfModels--;
	_models = new Model *[_numberOfModels];

	for(id_num i = 0; i < _numberOfModels; i++) {
		_models[i] = tmp[i];
	}

	delete[] tmp;

}

id_num Store::getNextVnum() {
	return ++_topVirtualNumber;
}

bool Store::exists(id_num vnum) {
	try {
		real(vnum);
	} catch (ModelNotFoundException) {
		return false;
	}
	return true;
}

id_num Store::real(id_num vnum) {
	id_num bottom, middle, top;

	bottom = 0;
	top = _numberOfModels;

	while (true) {
		if (top < bottom)
			throw ModelNotFoundException();

		middle = (top + bottom) / 2;

		if (_models[middle]->vnum() == vnum)
			return middle;

		if (vnum < _models[middle]->vnum())
			top = middle - 1;
		else
			bottom = middle + 1;

	}

}

void Store::order() {
	id_num inner, outer;

	Model *tmp;
	for(outer = 1; outer < _numberOfModels; outer++) {
		inner = outer;
		tmp = _models[inner];
		while(inner > 0 && _models[inner-1]->vnum() > tmp->vnum()) {
			_models[inner] = _models[inner-1];
			inner--;
		}
		_models[inner] = tmp;
	}
}

/********************************************************************************
 * END Store
 ********************************************************************************/
