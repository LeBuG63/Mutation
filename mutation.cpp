#include <iostream>
#include <ctime>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <vector>

typedef unsigned int u32_t;

class Mutation {
public:
    Mutation() {

    }

    ~Mutation() {
        delete m_individuID;
    }

    void	setIndividu(u32_t nindividu) {
        m_effectifIndividu = nindividu;

        m_individuID = new u32_t[m_effectifIndividu];

        std::cout << "ID de départ: ";

        for(u32_t i = 0; i < m_effectifIndividu; ++i) {
            m_individuID[i] = i;
            std::cout << m_individuID[i] << " ";
        }

        std::cout << std::endl;
    }

    void 	nextGeneration() {
        for(int actindividu = 0; actindividu < m_effectifIndividu; ++actindividu) {
            int chance = rand() % m_effectifIndividu + 1;

            for(int i = 0; i < chance; ++i) {
                m_listIndividu.push_back(m_individuID[actindividu]);
            }
        }

        for(int i = 0; i <  m_effectifIndividu; ++i) {
            int here = rand() % m_listIndividu.size();

            m_individuID[i] = m_listIndividu.at(here);

            std::cout << m_individuID[i] << " ";
        }

        std::cout << std::endl;

        m_listIndividu.clear();
    }

    void	processMutation() {
        u32_t   totalGeneration = 0;
        bool    winner = false;

        auto timeBegin = std::chrono::system_clock::now();

        while(!winner) {
            nextGeneration();
            ++totalGeneration;

            if(verifWin()) {
                winner = true;
            }
        }

        auto timeEnd = std::chrono::system_clock::now();

        std::chrono::duration<double> result = (timeEnd - timeBegin);

        std::cout << "Mutation gagnante " << m_individuWinner << " en " << totalGeneration << " générations (" << result.count() << "s)";
    }

    bool    verifWin() {
        bool    win = false;
        u32_t   tmp = m_individuID[0];

        for(int i = 1; i < m_effectifIndividu; ++i) {
            if(m_individuID[i] == tmp) {
                win = true;
                m_individuWinner = m_individuID[i];
            }
            else {
                win = false;
                i = m_effectifIndividu;
            }
        }
        return win;
    }

private:
    u32_t				m_effectifIndividu;
    u32_t 				*m_individuID;
    u32_t               m_individuWinner;
    std::vector<u32_t>	m_listIndividu;

};

int main(int argc, char *argv[]) {

    Mutation mutation;

    u32_t	nindividu;
    u32_t 	ngeneration;

    srand(time(NULL));

    std::cout << "Nombre d'individus: ";
    std::cin >> nindividu;

    mutation.setIndividu(nindividu);

    std::cout << std::endl;

    mutation.processMutation();

    return 0;
}