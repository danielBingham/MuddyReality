/***********************************************************************************
 * File: modelStore.cpp
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
 * or substantial portions of the Software.  *
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

template <class Model>
Store<Model>::Store() {
	_models = 0;
	_topVirtualNumber = 0;
	_numberOfModels = 0;
}

template <class Model>
Store<Model>::~Store() {
	if(_models != 0) {
		for(int i = 0; i < _numberOfModels; i++) {
			delete _models[i];
		}
		delete [] _models;
	}
}

template <class Model>
Model *Store<Model>::operator[](id_num rnum) {
	if(rnum >= _numberOfModels || rnum < 0) {
		return NULL;
	}
	return _models[rnum];
}

template <class Model>
id_num Store<Model>::size() {
	return _numberOfModels;
}

template <class Model>
Model *Store<Model>::get(id_num vnum) {
	id_num rnum = real(vnum);
	return _models[rnum];
}

template <class Model>
void Store<Model>::add(Model *model) {
	Model **tmp = NULL;

	tmp = new Model *[_numberOfModels];
	for(int i = 0; i < _numberOfModels; i++) {
		tmp[i] = _models[i];
	}
	delete [] _models;

	_models = new Model *[_numberOfModels+1];
	for(int i = 0; i < _numberOfModels; i++) {
		_models[i] = tmp[i];
	}
	delete [] tmp;

	_models[_numberOfModels] = model;
	_numberOfModels += 1;

	order();
}

template <class Model>
Model *Store<Model>::remove(id_num vnum) {
	id_num rnum = real(vnum);
	Model *removed = _models[rnum];
	
	Model ** tmp = NULL;

	tmp = new Model *[_numberOfModels-1];
	for(int i = 0; i < _numberOfModels-1; i++) {
		if(i >= rnum) {
			tmp[i] = _models[i+1];
		} else {
			tmp[i] = _models[i];
		}
	}

	delete [] _models;
	_models = new Model *[_numberOfModels-1];
	for(int i = 0; i < _numberOfModels-1; i++) {
		_models[i] = tmp[i];
	}
	delete [] tmp;
	
	_numberOfModels -= 1;
	
	return removed;
}	

template <class Model>
void Store<Model>::destroy(id_num vnum) {
	Model *removed = remove(vnum);
	delete removed;
}	

template <class Model>
id_num Store<Model>::getNextVnum() {
	return _topVirtualNumber+1;
}

template <class Model>
bool Store<Model>::exists(id_num vnum) {
	return (real(vnum) == -1);
}

template <class Model>
id_num Store<Model>::real(id_num vnum) {
	id_num bottom = 0, top = _numberOfModels, rnum = 0;

	while(top >= bottom) {
		rnum = (top-bottom)/2 + bottom;

		if(_models[rnum]->vnum() > vnum) {
			bottom = rnum+1;
		} else if(_models[rnum]->vnum() < vnum) {
			top = rnum-1;
		} else {
			return rnum;
		} 
	}
	return -1;
}

template <class Model>
void Store<Model>::order() {
	Model *tmp = NULL;
	int hole = 0;
	for(int sortedSize = 1; sortedSize < _numberOfModels-1; sortedSize++) {
		tmp = _models[sortedSize];
		hole = sortedSize;
		while (hole > 0 && tmp->vnum() > _models[hole-1]->vnum()) {
			_models[hole] = models[hole-1];
			hole -= 1;
		}
		_models[hole] = tmp;
	}
}
	

