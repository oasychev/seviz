#include "ModuleManager.h"
#include <tuple>
#include <iterator>
#include "modules/modules.h"

ModuleManager::ModuleManager(EpubRenderer& render) : m_render(render) {
    for (AbstractModule* m : registrar()) {
        m->m_engine = this;
        if (!m_container.contains(m->id())) {
            m_container.insert(m->id(), m);
        } else {
            destroy();
            throw DuplicateModulesException();
        }
    }
}

ModuleManager::~ModuleManager() {
    // Qt smart pointers can't be stored in Qt containers
    destroy();
}

void ModuleManager::bookOpened(Book* book) {
    m_book = book;
}

void ModuleManager::forEachModule(std::function<void(AbstractModule*)> functor) {
    for (AbstractModule* i : m_container) {
        functor(i);
    }
}

void ModuleManager::destroy() {
    for (AbstractModule* i : m_container) {
        delete i;
    }
    m_container.clear();
}

const Book& ModuleManager::getBook() {
    return *m_book;
}