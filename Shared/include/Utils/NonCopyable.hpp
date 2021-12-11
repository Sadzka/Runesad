//
// Created by Sadza on 19.06.2021.
//

#pragma once

#ifndef SADZA_NONCOPYABLE_HPP
#define SADZA_NONCOPYABLE_HPP


class NonCopyable
{
        protected:

        NonCopyable() {}

        ~NonCopyable() {}

        private:

        NonCopyable(const NonCopyable&);

        NonCopyable& operator=(const NonCopyable&);
};


#endif //SADZA_NONCOPYABLE_HPP
