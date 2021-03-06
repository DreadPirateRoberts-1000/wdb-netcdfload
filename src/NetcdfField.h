/*
 netcdfload

 Copyright (C) 2013 met.no

 Contact information:
 Norwegian Meteorological Institute
 Box 43 Blindern
 0313 OSLO
 NORWAY
 E-mail: post@met.no

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 MA  02110-1301, USA
 */

#ifndef NETCDFFIELD_H_
#define NETCDFFIELD_H_

#include "AbstractNetcdfField.h"
#include <fimex/DataDecl.h>
#include <boost/shared_array.hpp>

// remove?
#include "RawData.h"


namespace MetNoFimex
{
class SliceBuilder;
}
class NetcdfFile;

/**
 * Part of a variable in a NetcdfFile, extracted to hold exactly one valid time and dataversion.
 */
class NetcdfField : public AbstractNetcdfField
{
public:

	virtual ~NetcdfField();

	virtual const std::string & variableName() const
	{
		return variableName_;
	}

	virtual const IndexList & indexes() const { return indexList_; }

	virtual IndexList unHandledIndexes() const;

	virtual bool canHandleIndex(const std::string & name) const;

	virtual double indexValue(std::string dimension, unsigned index) const;

	virtual std::vector<Time> times() const;
	virtual std::vector<int> realizations() const;

	virtual std::string timeDimension() const;
	virtual std::string realizationDimension() const;
	virtual std::string xDimension() const;
	virtual std::string yDimension() const;

	virtual std::string attribute(const std::string & name) const;

	virtual Time referenceTime() const;

	virtual boost::shared_ptr<GridGeometry> placeSpecification() const;

	virtual boost::shared_ptr<AbstractDataRetriever> retriever(
			const LoadElement & loadElement,
			unsigned timeIndex, unsigned realizationIndex,
			const DataSpecification & querySpec) const;


protected:
	friend class NetcdfFile;
	NetcdfField(const NetcdfFile & netcdfFile, boost::shared_ptr<MetNoFimex::CDMReader> reader, const std::string & variableName);

	void rename(const std::string & newVariableName)
	{
		variableName_ = newVariableName;
	}

private:
	NetcdfField(); // undefined

	const NetcdfFile & netcdfFile_;
	boost::shared_ptr<MetNoFimex::CDMReader> reader_;
	std::string variableName_;
	IndexList indexList_;
	mutable std::map<std::string, boost::shared_array<double> > dimensionValues_;
};

#endif /* NETCDFFIELD_H_ */
