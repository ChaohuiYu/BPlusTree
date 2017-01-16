void createRelation(const std::string& relationName, const std::string& keyType, const int& recordLength);
void insertRecord(const std::string& relationName, const std::string& key, const std::string& record);
void deleteRecord(const std::string& relationName, const std::string& key);
void scanRelation(const std::string& relationName);
void queryRecord(const std::string& relationName, const std::string& key);
void rangeQueryRecords(const std::string& relationName, const std::string& key1, const std::string& key2);
void displayPage(const std::string& relationName, const std::string& pageId);
void statisticsRelation(const std::string& relationName);
