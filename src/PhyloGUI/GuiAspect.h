#ifndef GUIASPECT_H
#define GUIASPECT_H

#include <string>
#include "../Domain/INode.h"

namespace PhyloGui
{
    template <class T>
    class GuiAspect : public Domain::Node<GuiAspect<T> >
    {
    public:

        GuiAspect() : selected(false), expanded(true) {}

        ~GuiAspect() {}

        bool isSelected() const
        {
            return selected;
        }

        bool isExpanded() const
        {
            return expanded;
        }

        std::string getColor() const
        {
            return color;
        }

        void setSelected(const bool s)
        {
            selected = s;
        }

        void setExpanded(const bool e)
        {
            expanded = e;
        }

        void getColor(const std::string c)
        {
            color = c;
        }

    private:
        bool selected;
        bool expanded;
        std::string color;
    };
}

#endif

