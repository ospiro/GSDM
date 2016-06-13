#pragma once
#include "CandidateMethod.h"
#include "Motif.h"
#include "Graph.h"
#include "GraphProb.h"
#include <vector>
#include <utility>
#include <functional>

struct CandidateMthdFreqParm;

class CandidateMthdFreq :
	public CandidateMethod
{
	int nNode; // size of original graph
	int smin, smax;// size of motif [smin, smax]
	
	const CandidateMthdFreqParm* par;
public:
	static const std::string name;
	CandidateMthdFreq();

	virtual std::vector<std::pair<Motif, double>> getCandidantMotifs(const std::vector<Graph> & gs,
		const int smin, const int smax, const CandidateMethodParm& par);
private:
	void dfsMotif(std::vector<std::pair<Motif, double>>& mps, const int expNode,
		const std::vector<Graph>& gs, const CandidateMthdFreqParm& par, const GraphProb& gp);
	void dfsMotif2(std::vector<std::pair<Motif, double>>& res,
		const std::pair<Motif, double>& curr, const int expNode,
		const std::vector<Graph>& gs, const GraphProb& gp);
	void dfsMotif3(std::vector<std::pair<Motif, double>>& closed,
		std::vector<std::pair<Motif, double>>& open,
		const std::pair<Motif, double>& curr, const int expNode,
		const std::vector<Graph>& gs, const GraphProb& gp);

	std::vector<std::pair<Motif, double>> dfsMotif4(
		const std::pair<Motif, double>& curr, const int expNode,
		const std::vector<Graph>& gs, const GraphProb& gp);
	std::vector<std::pair<Motif, double>> dfsMotif5(
		const std::pair<Motif, double>& curr, const int expNode,
		const std::vector<Graph>& gs, const GraphProb& gp);
};

struct CandidateMthdFreqParm :
	public CandidateMethodParm
{
	double pMin;
	std::function<bool(double, double)> op_freq = std::less<double>();
	virtual void construct(const std::vector<std::vector<Graph>>& gPos, const std::vector<std::vector<Graph>>& gNeg);
};