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

        virtual bool isSelected() const
        {
            return selected;
        }

        virtual bool isExpanded() const
        {
            return expanded;
        }

        virtual std::string getColor() const
        {
            return color;
        }

        virtual void setSelected(const bool s)
        {
            selected = s;
        }

        virtual void setExpanded(const bool e)
        {
            expanded = e;
        }

        virtual void getColor(const std::string c)
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

