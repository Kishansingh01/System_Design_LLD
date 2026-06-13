#include<iostream>
#include<string>
using namespace std;

// Target interface expected by the client.
class IReports{
    public:
        // now takes the raw data string and return json
        virtual string getJsonData(const string& data)= 0;
        virtual ~IReports(){}
};
// 2. Adaptee provides XML data for a raw input
class XmlDataProvider{
    public:
        // Expect data in "name:id" format (e.g. "kishan:1")
        string getXmldata(const string& data){
            size_t sep=data.find(":");
            string name=data.substr(0,sep);
            string id=data.substr(sep+1);
        // Build an XML representation
        return "<user>"
                "<name>"+ name + "/name"
                "<id>"+id +"</id>"
                "</user>";
        }
};
// 3. Adapter : implements IReports by converting XML->JSON
class XmlDataProviderAdapter : public IReports{
    private:
        XmlDataProvider* xmlProvider;
    public:
        XmlDataProviderAdapter(XmlDataProvider* provider){
            this->xmlProvider= provider;
        }
        string getJsonData(const string& data) override {
            // 1. Get XML for the adaptee
            string xml= xmlProvider->getXmldata(data);
            // 2. Naivly parse out <name> and <id> values
            size_t startName= xml.find("<name>") + 6;
            size_t endName= xml.find("</name>");
            string name= xml.substr(startName,endName - startName);

            size_t startId= xml.find("<id>") + 4;
            size_t endId= xml.find("</id>");
            string id=xml.substr(startId,endId-startId);

            // Build and return JSON
            return "{\"name\":""+ name "+ "\",\"id\":"+id+"}";
        }
};
// 4. Client code works only with IReports
class Client{
    public:
        void getReport(IReports* report,string rawData){
            cout<<"Processed JSON"<<report->getJsonData(rawData)<<endl;
        }
};
 int main(){
    // 1. Create the adaptee
    XmlDataProvider* xmlProv= new XmlDataProvider();
    // 2.  MAke our adapter
    IReports* adapter= new XmlDataProviderAdapter(xmlProv);
    // 3. Give it some raw data
    string rawData= "Alice:42";
    // 4. Client prints the JSON
    Client* client= new Client();
    client->getReport(adapter,rawData);
    // -> Processed JSON: {"name":"Alice","id":42}
    
    // 5. CleanUp
    delete adapter;
    delete xmlProv;
    return 0;

 }