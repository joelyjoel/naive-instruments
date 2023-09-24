#include <algorithm>
#include <vector>

template <typename T>
class Breadcrumbs
{
private:
    std::vector<T*> list;

public:
    /**
     * Returns true if the item has been crumbed before, otherwise returns
     * false and records the item to the list.
     */
    bool crumb( T* item )
    {
        if ( std::find( list.begin(), list.end(), item ) != list.end() )
            return true;
        else
        {
            list.push_back( item );
            return false;
        }
    }

    /**
     * Returns true if the item has been crumbed before, otherwise returns
     * false and records the item to the list.
     */
    bool crumb( std::shared_ptr<T> item )
    {
        return crumb( item.get() );
    }

    /**
     * Returns true if the item has been crumbed before, otherwise returns
     * false and records the item to the list.
     */
    bool crumb( T& item )
    {
        crumb( &item );
    }
};
