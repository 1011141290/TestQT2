#include "stdafx.h"
#include "DataSet.h"

#include <boost/tokenizer.hpp>

DataSet::DataSet() { }


DataSet::~DataSet() {
	//free the memory automatically by their dector
	//records, preDefinedClusters
}

//////////////////////////////////////////////////
void DataSet::addClusterMember(std::string& clusterLabel, unsigned int recordId) {
	ClusterMembershipSet::reverse_iterator i = preDefinedClusters.rbegin();
	ClusterMembershipSet::reverse_iterator e = preDefinedClusters.rend();
	for (; i != e && i->getLabel() != clusterLabel; ++i);
	if (i == e) {  //it is a new cluster label
		ClusterMembership* pcd = new ClusterMembership();
		pcd->setLabel(clusterLabel);
		pcd->addMember(recordId);
		preDefinedClusters.push_back(pcd);
		return;
	}
	//found cluster identified by the clusterLabel
	i->addMember(recordId);
}
bool DataSet::parseRecord(const std::string& record, unsigned int labelColumn) {
	
    //
	//1) get line of reals, like [A 2.3 4.5 8.99], where A is cluster label
    //
    typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;
	boost::char_separator<char> sp(", \t;");
	Tokenizer tok(record, sp);

	static std::vector<double> buffer;				//temporary buffer for all record lines;
	buffer.clear();
	static std::string clusterLabel;

	double digit;
	unsigned int columnIndex = 0;				//column index starts from 0!
	for (const auto& str : tok) {
		if (columnIndex == labelColumn) {   //got cluster label
			clusterLabel.assign(str);
			++columnIndex;
			continue;
		}
		digit = std::atof(str.c_str());
		buffer.push_back(digit);
		++columnIndex;
	}


	//2) check whether dimensions are all same or not 
	unsigned int dim = buffer.size();
	unsigned int count = records.size();
	if (count > 0 && records[0].dim() != dim){
		std::cout << "DataSet.parseRecord...No. " << count + 1;
		std::cout << " record's dim=" << dim;
		std::cout << ", is not equal to the dim " << records[0].dim() << " of previous recorder";

		return false;
	}


	//add RecordId, starting from 0,
	//to the cluster identified by the clusterLabel
	addClusterMember(clusterLabel, records.size());

	//3) new Record2() and keep it to records
	records.push_back(new Record2(buffer));

	return true;
}
bool DataSet::isWhitespace(const std::string& str) const {
	for (auto& i : str) {
		if (std::isdigit(i) || i == '.' || std::isalpha(i) || i == '-')
			return false;
	}
	return true;
}
void DataSet::dumpCluster(std::ostream& out, const ClusterMembership& cd) const {
	out << cd.getLabel() << ":" << std::endl;
    for (auto& id : cd) {
		out << "[" << id << "]: ";
		records[id].dump(out);
		out << std::endl;
	}
}


//////////////////////////////////////////////
bool DataSet::parse(const std::string& fullPathFileName, unsigned int labelColumn /*= 0*/) {
	std::ifstream in(fullPathFileName);

    //clear all
    records.clear();
    preDefinedClusters.clear();

    if (!in.is_open()) {
		std::cout << "DataSet.parse...failed to open : " << fullPathFileName << std::endl;
		return false;
	}

	std::string record;
	for (; in; record.clear()) {
		std::getline(in, record);
		if (isWhitespace(record)) continue;		//pass the last line

		if (!parseRecord(record, labelColumn)) {
			return false;
		}
	}

	in.close();
	return true;
}
const ClusterMembershipSet& DataSet::getPreDefinedClusters() const {
	return preDefinedClusters;
}
unsigned int DataSet::dim() const {
	if (records.size() == 0) return 0;
	return records[0].dim();
}
const RecordSet2& DataSet::getRecords() const {
	return records;
}

void DataSet::dump(std::ostream& out) const {
	//summary info
	out << "total records: " << records.size() << std::endl;
	out << "clusters: " << preDefinedClusters.size() << std::endl;
	out << "dimension: " << dim() << std::endl;
	out << "----------------------------------------" << std::endl;

	//case 1: it has no cluster labels
	if (preDefinedClusters.size() == 0) {
		this->records.dump(out);
		return;
	}

	//case 2: it has cluster labels
	for (const auto& i : preDefinedClusters) {
		dumpCluster(out, i);
		out << "..................................." << std::endl;
	}
}

std::ostream& operator<<(std::ostream& out, const DataSet& ds) {
	ds.dump(out);
	return out;
}
