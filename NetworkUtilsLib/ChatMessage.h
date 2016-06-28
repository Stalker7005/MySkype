
namespace NetworkUtils{
#pragma pack(push, 1)
class ChatMessage
{
public:
    void SetData(char* data);
    char* GetData();

private:
    char* message;
};
#pragma pack(pop)
}