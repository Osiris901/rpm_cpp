#include <iostream>
#include <fstream>

using namespace std;

struct Pokemon
{
	Pokemon(string name = "Eevee", double const health = 55.0, unsigned const attack = 55, unsigned const defense = 50, unsigned const speed = 55)
		: name_(move(name)), health_(health), attack_(attack), defense_(defense), speed_(speed) {}
	virtual ~Pokemon() = default;

	void set_name(string name) { name_ = std::move(name); }
	void set_health(double const health) { health_ = health; }
	void set_attack(unsigned const attack) { attack_ = attack; }
	void set_defense(unsigned const defense) { defense_ = defense; }
	void set_speed(unsigned const speed) { speed_ = speed; }
	
	string const & get_name() const { return name_; }
	double get_health() const { return health_; }
	unsigned get_attack() const { return attack_; }
	unsigned get_defense() const { return defense_; }
	unsigned get_speed() const { return speed_; }

	virtual void print(ostream& stream) const
	{
		stream << name_ << "\n\t" << health_ << "\n\t" <<attack_ << "\n\t" << defense_ << "\n\t" << speed_ << endl;
	}

private:
	string name_;
	double health_;
	unsigned attack_;
	unsigned defense_;
	unsigned speed_;
};

struct RarePokemon : Pokemon
{
	RarePokemon(const string& name, double const health, unsigned const attack, unsigned const defense, unsigned const speed, unsigned special_attack,
		unsigned special_defense)
		: Pokemon(name, health, attack, defense, speed),
		  special_attack_(special_attack),
		  special_defense_(special_defense)
	{}

	void set_special_attack(unsigned special_attack) { special_attack_ = special_attack; }
	void set_special_defense(unsigned special_defense) { special_defense_ = special_defense; }

	unsigned get_special_attack() const { return special_attack_; }
	unsigned get_special_defense() const { return special_defense_; }

	void print(ostream& stream) const override
	{
		 Pokemon::print(stream);
		 stream << "\tSpecials:\n\t\tAttack: " << special_attack_ << "\n\t\tDefense: " << special_defense_ << endl;
	}
	
private:
	unsigned special_attack_;
	unsigned special_defense_;
};

int main()
{
	auto p1 = Pokemon();
	auto p2 = RarePokemon("Glaceon", 65.0, 60, 110, 65, 130, 95);
	auto p3 = RarePokemon("Vaporeon", 130.0, 65, 60, 65, 110, 95);

	ofstream pokemons;
	pokemons.open("pokemons.txt");
	p1.print(pokemons);
	p2.print(pokemons);
	p3.print(pokemons);
	pokemons.close();
	return 0;
}