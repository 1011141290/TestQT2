#pragma once

#include <string>
#include "ClusterMembershipSet.h"
#include "Record2.h"
#include "RecordSet2.h"

class DataSet
{
private:

	RecordSet2 records;
	ClusterMembershipSet preDefinedClusters;

private:
	void addClusterMember(std::string& clusterLabel, unsigned int recordId);
	bool parseRecord(const std::string& record, unsigned int labelColumn);
	bool isWhitespace(const std::string& str) const;
	void dumpCluster(std::ostream& out, const ClusterMembership& cd) const;

public:
	DataSet();
	~DataSet();
	bool parse(const std::string& fullPathFileName, unsigned int labelColumn = 0);
	const ClusterMembershipSet& getPreDefinedClusters() const;
	unsigned int dim() const;
	const RecordSet2& getRecords() const;

	void dump(std::ostream& out) const;

};

std::ostream& operator<<(std::ostream& out, const DataSet& ds);