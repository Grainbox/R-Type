/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** HitTag
*/

#ifndef HITTAG_HPP_
#define HITTAG_HPP_

class HitTag {
    public:
        enum hitTag {NONE, TAG1, TAG2};
        HitTag() = default;
        HitTag(hitTag tagValue) { tag = tagValue; };
        // HitTag(HitTag &other) { tag = other.tag; };

        hitTag tag = NONE;

        template<class Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & tag;
        }

    protected:
    private:
};

#endif
