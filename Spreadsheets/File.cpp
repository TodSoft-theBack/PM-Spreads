#include "File.h"

File::File(const char* path) : filename(path)
{
    stream.open(path, std::ios::in | std::ios::_Nocreate);

    if (!stream || !stream.is_open())
        throw std::runtime_error("Could not open file!!");
}

const std::fstream& File::Stream() const
{
    return stream;
}

std::fstream& File::Stream()
{
    return stream;
}

const String& File::Filename() const
{
    return filename;
}

const bool& File::HasChanged() const
{
    return hasChanged;
}

size_t File::CountMentions(char symbol)
{
    size_t pos = stream.tellg();
    stream.seekg(0, std::ios::beg);
    size_t count = 0;
    while (true)
    {
        char current = stream.get();
        if (stream.eof())
            break;
        if (current == symbol)
            count++;   
    }
    stream.clear();
    stream.seekg(pos);
    return count;
}

size_t File::CountLines()
{
    return CountMentions('\n');
}

std::ostream& File::Print(std::ostream& output) const
{
    return output << stream.rdbuf();
}

void File::EditAtPos(unsigned lineIndex, unsigned rowPos, const char* newValue)
{
    if (!hasChanged)
        hasChanged = true;
    size_t originalPos = stream.tellg();
    size_t lineCount = CountLines();
    stream.seekg(0, std::ios::end);
    size_t endPos = stream.tellg();
    stream.seekg(originalPos);
    size_t linePosLen = endPos / lineCount;

    size_t editPos = linePosLen * lineIndex + rowPos;
    originalPos = stream.tellp();
    stream.seekp(editPos, std::ios::beg);
    stream << newValue;
    stream.seekp(originalPos);
}

File::~File()
{
    stream.close();
}
