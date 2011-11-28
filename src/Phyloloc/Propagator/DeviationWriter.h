#ifndef DEVIATION_WRITER_H
#define DEVIATION_WRITER_H

namespace Propagation
{
    //TODO: Create DeviationWriter.cpp and write implementations in that file
    class DeviationWriter
    {
    public:
        DeviationWriter(const std::string& filename)
        {
            //TODO: Open file and save offstream for further writes
        }
        
        ~DeviationWriter()
        {
            //TODO: Close file
        }
        
        write(const std::string& treeName, const NodeName& nodeName, unsigned int iteration,
              ProbabilitiesConstIterator begin, ProbabilitiesConstIterator end)
        {
            //TODO: Write a single line to the stream, in the following format
            //   Treename, Nodename, iteration, begin, begin + 1, begin + 2....end
            //for example
            // Tree1, Node1, 3, 0.2, 0.23, 0.30, 0.28, 0.02
        }
    };
}

#endif
