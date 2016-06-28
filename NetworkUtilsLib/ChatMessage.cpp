#include "ChatMessage.h"
namespace NetworkUtils {

void ChatMessage::SetData(char* data)
{
    message = data;
}

char* ChatMessage::GetData()
{
    return message;
}

}

